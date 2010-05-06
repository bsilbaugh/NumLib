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

	OptimizerCG(Real bf_step=1.0, Real gs_reduction=0.1, Real tol=5.0E-3, Size max_iter_=1000):
		max_iter(max_iter_), delta_f_max(tol), line_search(bf_step, gs_reduction, tol)
	{}

	ErrorCode minimize(CostFunction& f, MinimumND<VectorType>& min)
	{

		// Get initial design...

		VectorType xopt(min.design());
		Real fopt = min.cost();

		// Set up temporary data structure...

		VectorType grad_prev(f.size());
		VectorType grad(f.size());
		VectorType dir(f.size());
		LineRes line_res(f, xopt, dir); /* this holds ref to xopt and dir! */
		Real delta_f;

		// Compute initial search direction (steepest descent)...

		f(min.design(), grad);
		dir = grad;
		dir *= -1.0;

		// Perform sequential line searches to find minimum...

		for(Index n=0; n<max_iter; ++n)
		{
			// Perform line search...

			Minimum1D line_min(0.0, fopt);

			ErrorCode code = line_search.minimize(line_res, line_min);

			if(code!=SUCCESS) return code;

			// Compute convergence criteria...

			delta_f = fopt - line_min.cost();

			// Update design and cost...

			xopt += line_min.design()*dir;
			fopt -= delta_f;

			// Check convergence and exit if satisfied...

			if( fabs(delta_f) < delta_f_max )
			{
				min.design(xopt, fopt);
				return SUCCESS;
			}
		
			// Update search direction...

			grad_prev = grad;

			f(xopt, grad);

			Real beta = prod(grad, grad - grad_prev)/prod(grad, grad);

			dir *= beta;
			dir += grad;

		}

		return EXCEEDED_MAX_ITER;

	}

private:

	typedef LineRestriction<CostFunction> LineRes;

	Size max_iter;

	Real delta_f_max;

	OptimizerBGQ< LineRes > line_search;

};

}}//::numlib::optimization

#endif
