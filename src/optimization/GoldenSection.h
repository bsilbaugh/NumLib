/*! \file GoldenSection.h
 *  \brief GoldenSection template definition
 */

#ifndef GOLDEN_SECTION_H
#define GOLDEN_SECTION_H

#include "../base/numlib-config.h"
#include "../base/nocopy.h"
#include "../base/debug_tools.h"

#include "optimization_error_codes.h"
#include "Minimum1D.h"

namespace numlib{ namespace optimization{

//! 1D optimizer based on Golden Section Search
/*!
 *	Implements the Golden Section Search algorithm. This may be used to
 *	directly estimate the optimum or to efficiently reduce an estimated
 *	search interval to a much smaller one. For most applications requiring
 *	a precise estimate of the optimum, the latter application is usually 
 *	best; i.e. Use a bracketing scheme to estimate the initial bounds on a 
 *	minimum, then use Golden section to reduce this estimate, then use a 
 *	quadratic fitting algorithm to refine the estimate of the optimum.
 *
 *	Template parameter CostFunction may be any callable class
 *	or function pointer.
 */
template<class CostFunction>
class GoldenSection
{
public:

	GoldenSection(Real reduction_ratio):
		rr(reduction_ratio)
	{}

	void reductionRatio(Real reduction_ratio) {rr = reduction_ratio;}

	Real reductionRatio() const {return rr;}

	ErrorCode minimize(CostFunction& f, Minimum1D& min)
	{

		// Initialize upper and lower bounds of search...

		Real a = min.lowerBound();
		Real b = min.upperBound();

		Real fa = min.costAtLowerBound();
		Real fb = min.costAtUpperBound();

		Real len = b - a;

		// Compute stopping criteria: maximum interval length...
	
		Real len_stop = rr*len;

		// Initialize interior sample point locations and function values...

		Real alpha1 = b - tau*len;
		Real alpha2 = a + tau*len;

		Real f1 = f(alpha1);
		Real f2 = f(alpha2);

		// Reduce bounds on minimum...

		while(len > len_stop)
		{
			if( f1 > f2 )
			{
				/* Min cannot be in [a, alpha2] */

				// Move lower bound to the right ...

				a = alpha1;
				fa = f1;
				len = b - a;

				alpha1 = alpha2;
				f1 = f2;

				// Compute new left interior point...

				alpha2 = a + tau*len;
				f2 = f(alpha2);
			}
			else if( f1 < f2 )
			{
				/* Min cannot be in [alpha1, b] */

				// Move upper bound to the left ...
				
				b = alpha2;
				fb = f2;
				len = b - a;

				alpha2 = alpha1;
				f2 = f1;

				// Compute new right interior point...

				alpha1 = b - tau*len;
				f1 = f(alpha1);
			}
			else
			{
				/* f1 == f2 => min inside [alpha1, alpha2] */

				// Take alpha1 and alpha2 and new upper and lower bound, and 
				// compute new interior points...

				a = alpha1;
				fa = f1;

				b = alpha2;
				fb = f2;

				len = b - a;

				alpha1 = b - tau*len;
				alpha2 = a + tau*len;

				f1 = f(alpha1);
				f2 = f(alpha2);

			}
		}

		// Find smallest interval containing min and set solution...

		if( f1 > f2 )
		{
			ASSERT( !(f2 > fb) );

			min.lowerBound(alpha1, f1);
			min.upperBound(b, fb);
			min.design(alpha2, f2);

		}
		else
		{
			ASSERT( !(f1 > fa) );

			min.lowerBound(a, fa);
			min.upperBound(alpha2, f2);
			min.design(alpha1, f1);
		}

		return SUCCESS;
	}

private:

	DISALLOW_COPY_AND_ASSIGN( GoldenSection );

	// Golden ratio
	static
	const Real tau = 0.61803398875;

	// Require interval reduction ratio
	Real rr;

};

}}//::numlib::optimization

#endif
