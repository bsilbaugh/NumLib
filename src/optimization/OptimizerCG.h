/*! \file OptimizerCG.h
 *  \brief OptimizerCG template definition
 */

#ifndef OPTIMIZER_CG_H
#define OPTIMIZER_CG_H

#include "optimization_error_codes.h"
#include "Minimum1D.h"
#include "MinimumND.h"
#include "LineRestriction.h"
#include "OptimizerBGQ.h"

namespace numlib{ namespace optimization{

template<class CostFunction>
class OptimizerCG
{
public:

	typedef typename CostFunction::VectorType VectorType;

	typedef MinimumND<VectorType> Minimum;

	OptimizerCG(Size dim, Real bf_step=1.0, Real gs_reduction=0.1, Real tol_=5.0E-3, Size max_iter_=1000):
		n(dim), tol(tol_), max_iter(max_iter_), dir(n), grad(n),
		line_search(bf_step, gs_reduction, tol)
	{}

	//! Sets convergence tolerance used to terminate execution of OptimizerCG::minimize
	void tolerance(Real tol_) {tol = tol_;}

	//! Returns tolerance used to terminate execution of OptimizerCG::minimize
	const Real tolerance() const {return tol;}

	//! Sets maximum allowable iterations executed by OptimizerCG::minimize
	void maxIteration(Size max_iter_) {max_iter = max_iter_;}

	//! Sets maximum allowable iterations executed by OptimizerCG::minimize
	const Size maxIteration() const {return max_iter;}

	//! Resets optimizer to begin a new iteration sequence...
	ErrorCode newSequence(CostFunction& f, const Minimum& min)
	{
		// Compute initial search direction (steepest descent)...

		f(min.design(), grad);
		dir  = grad;
		dir *= -1.0;

		return SUCCESS;
	}

	//! Returns search direction to be used during next call to iter
	/*!
	 *  This is provided for monitoring purposes and can otherwise
	 *  be ignored.
	 */
	const VectorType& searchDirection() const {return dir;}

	//! Executes one iteration: refines the optimum design estimate
	ErrorCode iter(CostFunction& f, Minimum& min)
	{
		VectorType xopt = min.design();
		Real fopt = min.cost();

		// Set up restriction of f to 1-dimensional subspace...

		LineRes line_res(f, xopt, dir);

		// Execute line search...

		Minimum1D line_min(0.0, fopt);

		ErrorCode code = line_search.minimize(line_res, line_min);

		if(code!=SUCCESS) return code;

		// Update design and cost...

		xopt += line_min.design()*dir;
		fopt  = line_min.cost();

		min.design(xopt, fopt);

		// Update search direction using Polak-Ribiere formula...

		VectorType grad_prev(grad);

		f(xopt, grad);

		Real beta = prod(grad, grad - grad_prev)/prod(grad, grad);

		dir *= beta;
		dir += grad;

		return SUCCESS;

	}

	//! Executes a complete optimization sequence until convergence or falure
	/*!
	 *  This is essentially a wrapper around OptimizerCG::newSequence and
	 *  OptimizerCG::iter. If neither solution monitoring, intermediate 
	 *  processing, nor special termination rules for the iteration sequence 
	 *  are needed, then this function may be called in place of 
	 *  OptimizerCG::newSequence and OptimizerCG::iter. However, this function 
	 *  does not need to be called if the user is explicitly calling 
	 *  OptimizerCG::newSequence and OptimizerCG::iter from within their own 
	 *  "minimize" function.
	 *
	 *  For those needing a tighter integration of OptimizerCG with another 
	 *  component, the implementation of this function may also be used as an 
	 *  example of how OptimizerCG::newSequence and OptimizerCG::iter are used 
	 *  to compute an optimal solution.
	 */
	ErrorCode minimize(CostFunction& f, Minimum& min)
	{
		ErrorCode code = SUCCESS;

		// Initialize optimization search...

		code = newSequence(f, min);

		if(code!=SUCCESS) return code;

		// Sequentially perform line searches...

		for(Index n=0; n<max_iter; ++n)
		{

			Real fopt = min.cost();

			// Execute line search and check for error...
		
			code = iter(f, min);
			if(code!=SUCCESS) return code;

			// Check convergence criteria...

			Real delta_f = fopt - min.cost();
			if(fabs(delta_f) < tol) return code;
		}

		return EXCEEDED_MAX_ITER;
	}

private:

	DISALLOW_COPY_AND_ASSIGN( OptimizerCG );

	typedef LineRestriction<CostFunction> LineRes;

	Size n;

	Real tol;

	Size max_iter;

	VectorType dir;

	VectorType grad;

	OptimizerBGQ< LineRes > line_search;

};

}}//::numlib::optimization

#endif
