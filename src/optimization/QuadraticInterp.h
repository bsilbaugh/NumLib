/*! \file QuadraticInterp.h
 *  \brief QuadraticInterp template definition
 */

#ifndef QUADRATIC_INTERP_H
#define QUADRATIC_INTERP_H

#include "../base/numlib-config.h"
#include "../base/nocopy.h"

#include "optimization_error_codes.h"
#include "Minimum1D.h"

namespace numlib{ namespace optimization{

//! 1D optimizer based on quadratic fittting
/*!
 *  Implements a sequential quadratic fitting algorithm to estimate
 *  the optimum of a 1D cost function. 
 *
 *  NOTE: This does not update the estimates for the upper and lower
 *  bound of the minimum. Numerical experiments have shown that these
 *  estimates may be in error if the convergence is oscillatory. If
 *  tight estimates on the upper and lower bound of the minimum are
 *  needed, it seems better to use golden section search for this
 *  purpose (which may be used to start this scheme).
 *
 *  The template parameter CostFunction may be any callable class
 *  or function pointer.
 */
template<class CostFunction>
class QuadraticInterp
{
public:

	QuadraticInterp(Real delta_f_max_):
		delta_f_max(delta_f_max_)
	{}

	void tolerance(Real delta_f_max_) {delta_f_max = delta_f_max_;}

	Real tolerance() const {return delta_f_max;}

	ErrorCode minimize(CostFunction& f, Minimum1D& min)
	{
		// Initialize stencil...

		Real alpha0 = min.lowerBound();
		Real alpha1 = min.design();
		Real alpha2 = min.upperBound();

		Real f0 = min.costAtLowerBound();
		Real f1 = min.cost();
		Real f2 = min.costAtUpperBound();

		Real alpha_opt = alpha1;
		Real f_opt = f1;

		Real delta_f = 0;

		// Find optimum...
	
		do
		{
			// Estimate new optimum from quadratic fit...

			Real p0 = alpha0*alpha0;
			Real p1 = alpha1*alpha1;
			Real p2 = alpha2*alpha2;

			Real nterm1 = f0*(p1 - p2);
			Real nterm2 = f1*(p2 - p0);
			Real nterm3 = f2*(p0 - p1);

			Real dterm1 = f0*(alpha1 - alpha2);
			Real dterm2 = f1*(alpha2 - alpha0);
			Real dterm3 = f2*(alpha0 - alpha1);

			Real den = dterm1 + dterm2 + dterm3;

			alpha_opt = 0.0;
			if(den != 0) alpha_opt = 0.5*(nterm1 + nterm2 + nterm3)/den;

			f_opt = f(alpha_opt);

			// Compute decrease in cost function...

			delta_f = f1 - f_opt;

			// Update bounds on minimum...

			/* NOTE: delta_f would be zero if alpha_opt == alpha1 */

			if( alpha_opt < alpha1 )
			{
				/* min is bounded above by alpha1 */

				alpha2 = alpha1;
				f2 = f1;

			}
			else
			{
				/* min is bounded below by alpha1 */

				alpha0 = alpha1;
				f0 = f1;

			}

			// Store current estimate for next iteration...

			alpha1 = alpha_opt;
			f1 = f_opt;

		}while(fabs(delta_f) > delta_f_max);

		// Set optimum estimate
		min.design(alpha1, f1);

		/* NOTE: WE don't report the updated bounds since oscillatory 
		 * convergence may actually cause these estimates to be incorrect. It 
		 * seems better to keep the initial estimate (e.g. that provided by a 
		 * golden section search) */

		return SUCCESS;

	}

private:

	Real delta_f_max;

};

}}//::numlib::optimization

#endif
