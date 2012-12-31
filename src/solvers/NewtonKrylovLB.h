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
	NewtonKrylovLB(NL& f_, Size n_, Size mmax_, T alpha_, T beta_);

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
			min_quadratic_strategy(conv_crit, conv_hist, fu, fup);
	    } else if(beta_failed){
			/* If we're here, then Newton step is too small. */
			// Scale up by doubling lambda...
			doubling_strategy(conv_crit, conv_hist);
		}

		// Correct any overshoots, if any...
		if(!conv_crit.both_satisfied()){
			successive_linear_interp_strategy(conv_crit, conv_hist, fu, fup);
		}

		// Let's be sure that criteria has been satisfied...
		if(!conv_crit.both_satisfied()){
			throw numlib::NumLibError("Backtracking failed in NewtonKrylovLB::iter");
		}
		
		// Return result...
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
			T lamda;
			T fu;
			Elem(T lambda_, T fu_):lambda(lambda_),fu(fu_){}
		};

		ConvHist():data(){}

		ConvHist& append(const Elem& elem)
		{
			data.push_back(elem);
			return *this;
		}

		ConvHist& append(const T& lambda, const T& fu)
		{
			return append(Elem(lambda,fu));
		}
		
		const SolnPair& first() const
		{
			return data.front();
		}
		
		const SolnPair& last() const
		{
			return data.back();
		}
		
		const SolnPair& second_last() const
		{
			return *(++(data.rend()));
		}
		
	private:
		typedef typename std::list< Elem > Data;
		Data data;
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
				 const T& fu, const T& fup, 
				 const T& alpha_, const T& beta):
			alpha(alpha_),beta(beta_),fu(0),fup(0),
			u(u_),du(du_),u_new(u_.size()),r_new(u_.size()),
			f(f_) {}

		bool check(const T& lam)
		{
			// Compute objective function...
			u_new = du;
			u_new *= lam;
			u_new += u;
			f.eval(u_new,r_new);
			fu_new = 0.5*prod(r_new,r_new);

			// Check alpha condition (upper limit)...
			alpha_check = !(fu_new > fu + alpha*lam*fup);

			// Check beta condition (lower limit)...
			beta_check = !(fu_new < fu + beta*lam*fup);
			
			// Return true if both conditions satisfied...
			return alpha_check and beta_check;
		}

		const T& alpha() const 
		{
			return alpha;
		}
		
		const T& beta() const
		{
			return beta;
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
			fu_new;
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
		const T alpha, beta, fu, fup;
		const VecType u, du;
		T fu_new;
		VecType u_new, r_new;
		NL& f;
				
	};

/*----------------------------------------------------------------------------*/
/*                                                                Member data */

	Size n;             /* nonlinear operator rank */
	NL& f;              /* nonlinear operator */

/*----------------------------------------------------------------------------*/
/*                                                           Helper functions */

	// Computes the newton correction vector 'du'
	void newton_correction(const VecType& r, const VecType& u, VecType& du, VecType& rlin)
	{
		// Setup finite difference operator...
		GateauxFD<T,NL> gateaux(f, u, fu);

		// Set tolerance used to determine "happy breakdown"...
		const T breakdown_tol=0.5E-6;

		// Compute Newton correction using Krylov solver...
		// -- we'll do a little trick: 
		// -- first solve J(u)*du = f(u), instead of J(u)*du = -f(u)
		// -- then fix sign in-place, du = -du;
		rn = krylov.solve(gateaux, du, r, breakdown_tol, rlin);
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
			cond = crit.beta_satisfied();
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
			lambda = min(0.1, lambda);
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
		
		// Now interpolate a new lambda value that satisfies both conditions...
		const T alpha = conv_hist.alpha();
		do{
			T m = (fu_hi - fu_low)/(lambda_hi - lambda_low);
			T lambda = (fu0 - fu_low + m*lambda_low)/(m - alpha*fup0);
			conv_crit.check(lambda);
			const T fu = conv_crit.objective_function_value();
			conv_hist.append(lambda, fu);
			if(conv_crit.both_satisfied){
				return;
			} else if(conv_hist.alpha_satisfied){
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
