/*! \file NewtonKrylovLB.h */

#ifndef NEWTON_KRYLOV_LB_H
#define NEWTON_KRYLOV_LB_H

#include <list>
#include "Krylov.h"
#include "GateauxFD.h"

namespace numlib{ namespace solver{

//! Newton-Krylov solver with Linesearch Backtracking
/*!
 *  This class iteratively solves problems of the form:
 *      f(v) = 0
 *  where f is a nonlinear map of rank n, and v is an n-dim vector.
 *
 *  This implements a Jacobian-Free Newton-Krylov Algorithm with
 *  Linesearch Backtracking. In theory, this algorithm should be globally
 *  convergent; however, since the algorithm is based on minimizing the residual
 *  norm, it is possible that it may converge to a local minima (spurious
 *  solution). Should this happen, you will need to restart the algorithm with a
 *  different initial guess.  For more information, see the paper: Brown and
 *  Saad. "Hybrid Krylov Methods for Systems of Nonlinear Equations." SIAM
 *  J. Sci. Stat. Comput. Vol 11, No 3, pp. 450-481, May 1990.
 * 
 *  This template may be used with any type, f, which implements the nonlinear
 *  operator interface f(u,r), where u is the approximate solution vector and r
 *  is the (returned) residual vector corresponding to u. Note, the alternative
 *  interface r = f(u) is more syntatically pleasing; however, this results in
 *  frequent construction, copying, and deletion of potentially large vectors.
 *  
 *  Template arguments:
 *  T.... Numeric type (e.g. numlib::Real)
 *  NL... Nonlinear operator type
 *  K.... Krylov space type
 *  P.... Krylov projection operator type
 *
 *  The design of this class deviates a bit from the NewtonKrylov class.  After
 *  some deliberation, it was decided that it would be easier, and
 *  computationally more efficient, to encapsulate this algorithm into a single
 *  class rather than try to reuse the existing NewtonKrylov class (which would
 *  have required some refactoring anyway). Furthermore, there are some aspects
 *  of the NewtonKrylov class interface that, in retrospect, make it awkward to
 *  use. For example, the NewtonKrylov class posses state (the residual vector),
 *  wherease this classes does not posses any state (only static parameters).
 */
template<class T, class NL, class K, class P>
class NewtonKrylovLB
{
public:

	typedef linalg::Vector<T> VecType;
	typedef Krylov<T,GateauxFD<T,NL>,K,P> KrylovSolver;

	//! Initializes solver
	/*!
	 *  Sets internal reference to the nonlinear operator f,
	 *  and allocates internal memory required by algorithm.
	 *
	 *  Arguments:
	 *    f: nonlinear operator
	 *    n: rank of nonlinear operator
	 *    mmax: maximum krylov subspace dimension
	 *    alpha: slope scaling factor (upper limit)
	 *    beta: slope scaling factor (lower limit)
	 */
	NewtonKrylovLB(NL& f_, Size n_, Size mmax_, T alpha_, T beta_, T lambda_min_):
		f(f_),n(n_),mmax(mmax_),alpha(alpha_),beta(beta_),lambda_min(lambda_min_)
	{}

	//! Executes a single iteration of the nonlinear solver
	/*!
	 *  Upon input, u should contain the current solution estimate, and r should
	 *  be the corresponding (nonlinear) residual vector.  Upon output, u
	 *  contains the updated solution estimate, and r contains the updated
	 *  residual vector. (Remember, r = f(u).)
	 */
	T iter(VecType& u, VecType& r)
	{
		// Check dimensions...
		ASSERT( u.size() == n );
		ASSERT( r.size() == n );

		// Setup working variables...
		VecType du(n); /* Newton correction vector */
		VecType rlin(n); /* linear residual vector */

		// Compute approximate newton correction vector...
		newton_correction(r, u, du, rlin);

		// Compute value of objective function and it's derivative..
		const T fu = 0.5*prod(r,r);
		const T fup = -2.0*fu - prod(r,rlin);

		// Initialize convergence history...
		ConvHist conv_hist;
		conv_hist.append(0.0, fup);

		// Initialize convergence criteria...
		ConvCrit conv_crit(f, u, du, fu, fup, alpha, beta);

		// Try full Newton step...
		full_step_strategy(conv_crit, conv_hist);

		// Apply backtracking if full Newton step did not satisfy both alpha
		// beta conditions...
		const bool alpha_failed = !conv_crit.alpha_satisfied();
		const bool beta_failed = !conv_crit.beta_satisfied();
		if(alpha_failed){
			/* If we're here, then Newton step is too big. */
			// Scale back by fitting a quadratic and finding its minimum...
			// -- Remember, this will always reduce lambda.
			DEBUG_PRINT("Applying min quad strategy");
			min_quadratic_strategy(conv_crit, conv_hist, fu, fup);
	    } else if(beta_failed){
			/* If we're here, then Newton step is too small. */
			// Scale up by doubling lambda...
			DEBUG_PRINT("Applying doubling strategy");
			doubling_strategy(conv_crit, conv_hist);
		}

		// Correct any overshoots, if any...
		if(!conv_crit.both_satisfied()){
			DEBUG_PRINT("Applying successive linear interp");
			successive_linear_interp_strategy(conv_crit, conv_hist, fu, fup);
		}

		// Let's be sure that criteria has been satisfied...
		if(!conv_crit.both_satisfied()){
			throw numlib::NumLibError("Backtracking failed in NewtonKrylovLB::iter");
		}
		
		// Return result...
		DEBUG_PRINT("Returning result");
		u = conv_crit.soln_vector();
		r = conv_crit.residual_vector();
		return norm2(r);

	} // iter

private:

	DISALLOW_COPY_AND_ASSIGN( NewtonKrylovLB );

/*----------------------------------------------------------------------------*/
/*                                                Helper classes and typedefs */

	class ConvHist
	{
	public:

		struct Elem
		{
			T lambda;
			T fu;
			Elem(T lambda_, T fu_):lambda(lambda_),fu(fu_){}
		};

		ConvHist():data(),log_file("newton_krylov_conv.log"){}

		~ConvHist()
		{
			log_file.close();
		}

		ConvHist& append(const Elem& elem)
		{
			data.push_back(elem);
			return *this;
		}

		ConvHist& append(const T& lambda, const T& fu)
		{
			DEBUG_PRINT_VAR(lambda);
			log_file<<lambda<<" "<<fu<<std::endl;
			return append(Elem(lambda,fu));
		}
		
		const Elem& first() const
		{
			return data.front();
		}
		
		const Elem& last() const
		{
			return data.back();
		}
		
		const Elem& second_last() const
		{
			return *(++(data.rbegin()));
		}
		
	private:
		typedef typename std::list< Elem > Data;
		Data data;
		std::ofstream log_file;
	};

	//! Model of the Goldstien-Armijo conditions
	/*!
	 *  The Goldstien-Armijo conditions consist of two inequalities
	 *  that provide sufficient conditions for global convergence. These
	 *  are also known as the alpha-beta conditions.
	 */
	class ConvCrit
	{
	public:

		ConvCrit(NL& f_, 
				 const VecType& u_, const VecType& du_, 
				 const T& fu_, const T& fup_, 
				 const T& alpha, const T& beta):
			a(alpha),b(beta),fu(fu_),fup(fup_),
			u(u_),du(du_),u_new(u_.size()),r_new(u_.size()),
			f(f_) 
		{
			DEBUG_PRINT_VAR( fu );
			DEBUG_PRINT_VAR( fup );
		}

		bool check(const T& lam)
		{
			// Compute objective function...
			u_new = du;
			u_new *= lam;
			u_new += u;
			f.eval(u_new,r_new);
			fu_new = 0.5*prod(r_new,r_new);

			DEBUG_PRINT_VAR( lam );
			DEBUG_PRINT_VAR(fu_new);

			// Check alpha condition (upper limit)...
			alpha_check = !(fu_new > fu + a*lam*fup);

			DEBUG_PRINT_VAR( alpha_check );

			// Check beta condition (lower limit)...
			beta_check = !(fu_new < fu + b*lam*fup);

			DEBUG_PRINT_VAR( beta_check );
			
			// Return true if both conditions satisfied...
			return alpha_check and beta_check;
		}

		const T& alpha() const 
		{
			return a;
		}
		
		const T& beta() const
		{
			return b;
		}
		
		const bool alpha_satisfied() const
		{
			return alpha_check;
		}
		
		const bool beta_satisfied() const
		{
			return beta_check;
		}

		const bool both_satisfied() const
		{
			return alpha_check and beta_check;
		}
		
		const T& objective_function_value() const
		{
			return fu_new;
		}
		
		const VecType& soln_vector() const
		{
			return u_new;
		}
		
		const VecType& residual_vector() const
		{
			return r_new;
		}

	private:

		bool alpha_check, beta_check;
		const T a, b, fu, fup;
		const VecType u, du;
		T fu_new;
		VecType u_new, r_new;
		NL& f;
				
	};

/*----------------------------------------------------------------------------*/
/*                                                                Member data */
	NL& f;              /* nonlinear operator */
	Size n;             /* nonlinear operator rank */
	Size mmax;
	T alpha;
	T beta;
	T lambda_min;

/*----------------------------------------------------------------------------*/
/*                                                           Helper functions */

	// Computes the newton correction vector 'du'
	void newton_correction(const VecType& r, const VecType& u, VecType& du, VecType& rlin)
	{
		// Setup finite difference operator...
		GateauxFD<T,NL> gateaux(f, u, r);

		// Setup Krylov solver...
		KrylovSolver krylov_solver(n,mmax);

		// Set tolerance used to determine "happy breakdown"...
		const T breakdown_tol=0.5E-6;

		// Compute Newton correction using Krylov solver...
		// -- we'll do a little trick: 
		// -- first solve J(u)*du = f(u), instead of J(u)*du = -f(u)
		// -- then fix sign in-place, du = -du;
		T rn = krylov_solver.solve(gateaux, du, r, breakdown_tol, rlin);
		du *= -1.0;

		/************************************************************************
		 * At this point, du should contain the newton correction, and rlin
		 * should contain the residual of the linearized system.
         ************************************************************************/
	}

	void full_step_strategy(ConvCrit& conv_crit, ConvHist& conv_hist)
	{
		const T lambda = 1.0;
		conv_crit.check(lambda);
		const T fu = conv_crit.objective_function_value();
		conv_hist.append(lambda, fu);
	}
	
	void doubling_strategy(ConvCrit& conv_crit, ConvHist& conv_hist)
	{
		T lambda = conv_hist.last().lambda;
		bool cond(true);
		while(cond){
			lambda *= 2.0;
			conv_crit.check(lambda);
			cond = conv_crit.beta_satisfied();
			const T fu = conv_crit.objective_function_value();
			conv_hist.append(lambda, fu);
		}
	}
		
	void min_quadratic_strategy(ConvCrit& conv_crit, ConvHist& conv_hist,
								const T& fu0, const T& fup0)
	{
		T lambda = conv_hist.last().lambda;
		T fu = conv_hist.last().fu;
		bool cond(true);
		while(cond){
			lambda = -0.5*fup0*lambda*lambda/(fu - fu0 - fup0*lambda);
			lambda = min(lambda_min, lambda);
			conv_crit.check(lambda);
			cond = conv_crit.alpha_satisfied();
			const T fu = conv_crit.objective_function_value();
			conv_hist.append(lambda, fu);
		}
	}
	
	void successive_linear_interp_strategy(ConvCrit& conv_crit, ConvHist& conv_hist,
										   const T& fu0, const T& fup0)
	{
		// Find lambda low and high...
		T lambda_hi, fu_hi;
		T lambda_low, fu_low;
		if(conv_hist.last().lambda > 1){
			/******************************************************************
			 * If we're here, then the doubling strategy overshot the upper
			 * bound (alpha condition), while increasing lambda. Furthermore,
			 * the second to the last lambda in the conv history does not
			 * satisfy the lower bound (beta condition) alpha condition.
			 ******************************************************************/
			lambda_hi = conv_hist.last().lambda;
			fu_hi = conv_hist.last().fu;
			lambda_low = conv_hist.second_last().lambda;
			fu_low = conv_hist.second_last().fu;
		} else {
			/*******************************************************************
			 * If we're here, then the min_quadratic overshot the lower bound
			 * (beta condition) while reducing lambda. Furthermore, the second
			 * to last lambda in the conv history does not satisfy the upper
			 * bound (alpha condition).
			 *******************************************************************/
			lambda_low = conv_hist.last().lambda;
			fu_low = conv_hist.last().fu;
			lambda_hi = conv_hist.second_last().lambda;
			fu_hi = conv_hist.second_last().fu;
		}

		DEBUG_PRINT_VAR( lambda_hi );
		DEBUG_PRINT_VAR( lambda_low );
		
		// Now interpolate a new lambda value that satisfies both conditions...
		const T alpha = conv_crit.alpha();
		while(true){
			const T m = (fu_hi - fu_low)/(lambda_hi - lambda_low);
			const T den = m - alpha*fup0;
			if(numlib::is_zero(den))
				throw numlib::NumLibError("Division by zero in NewtonKrylovLB linear interp");
			T lambda = (fu0 - fu_low + m*lambda_low)/den;
			conv_crit.check(lambda);
			const T fu = conv_crit.objective_function_value();
			conv_hist.append(lambda, fu);
			if(conv_crit.both_satisfied()){
				return;
			} else if(conv_crit.alpha_satisfied()){
				/********************************************************
				 * If we're here, then the new lambda value is too small
				 * and should be taken as the new lower lambda value.
				 ********************************************************/
				lambda_low = lambda;
				fu_low = fu;
			} else {
				/***********************************************************
				 * If we're here, then the new lambda value is too big and
				 * should be taken as the new upper lambdas value.
				 ***********************************************************/
				lambda_hi = lambda;
				fu_hi = fu;
			}
		}
	}
		
}; // class NewtonKrylovLB

}}//::numlib::solver

#endif
