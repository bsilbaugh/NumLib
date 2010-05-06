/*! \file BracketFinder.h
 *  \brief BracketFinder class definition
 */

#ifndef BRACKET_FINDER_H
#define BRACKET_FINDER_H

#include "../base/numlib-config.h"
#include "../base/nocopy.h"

#include "optimization_error_codes.h"
#include "Minimum1D.h"

namespace numlib{ namespace optimization{

//! Estimates the upper and lower bound of the minimum using the bracket method
/*!
 *  The upper and lower bound of the minimum are estimated using the
 *  a simple bracket method with constant user defined step size. Starting
 *  from an initial estimate for the optimum, the cost function is sequentially 
 *  sampled at uniform points defined by the step size. The sampling is terminated
 *  when a subinterval is identified where the cost function is strickly convex.
 *  It is assumed that the existence of a lower bound on the cost function has
 *  been verified.
 * 
 * 	Template parameter CostFunction should either be a callable class (functor)
 * 	or function pointer.
 */
template<class CostFunction>
class BracketFinder
{
public:

	//! Initilizes parameters used by the bracket method
	/*!
	 *  step_size := constant step size used to scan for upper and lower bounds
	 *  lower_bound := lower bound on search domain
	 *  upper_bound := upper bound on search domain
	 */
	BracketFinder(Real step_size, Real lower_bound=-2.0E3, Real upper_bound=2.0E3):
		delta(step_size), alpha_min(lower_bound), alpha_max(upper_bound)
	{}

	void stepSize(Real step_size) {delta = step_size;}

	Real stepSize() const {return delta;}

	void lowerBound(Real lower_bound) {alpha_min = lower_bound;}

	Real lowerBound() const {return alpha_min;}

	void upperBound(Real upper_bound) {alpha_max = upper_bound;}

	Real upperBound() const {return alpha_max;}

	//! Executes bracket method
	/*!
	 *  Upon input, the optimimum estimate is taken to be the starting point of 
	 *  the search. Upon output 2 conditions are possible:
	 *
	 *  1. The bounds on a minimum were found. The lower and upper bounds
	 *     of f were updated accordingly and the optimum estimated was
	 *     set to the mid point of the interval containing the minimum.
	 *
	 *     Returns ErrorCode value SUCCESS.
	 *
	 *  2. Multiple minima were detected. The lower and upper bounds of
	 *     f, as well as the optimum estimate, remain as they were upon input.
	 *
	 *     Returns ErrorCode value MULTIPLEMIN.
	 *
	 *  3. No minimum was found - reached user defined search limits.
	 *
	 *     Returns ErrorCode value NOMIN.
	 *
	 *  The returned error codes are set based on a rather limited set of
	 *  information. The user should use caution when interpreting these
	 *  values.
	 */
	ErrorCode minimize(CostFunction& f, Minimum1D& min)
	{
		// Get starting point and corresponding function value...

		alpha0 = min.design();
		f0 = min.cost();

		// Set preferred search direction (to resolve an initial "flat spot")
		dir = 1.0;

		// Initialize stencile...

		alpha1 = alpha0 + delta;
		f1 = f(alpha1);

		alpha2 = alpha1 + delta;
		f2 = f(alpha2);

		// Attempt to bracket minimum...

		while( ( alpha0 >= alpha_min) and (alpha2 <= alpha_max) )
		{
			// Check for minimum...

			if( (f0 > f1) and (f1 < f2) )
			{
				/* found bounds on minimum */

				// Set estimated bounds on minimum ...

				min.lowerBound(alpha0, f0);
				min.upperBound(alpha2, f2);
				min.design(alpha1, f1);

				return SUCCESS;
			}

			// Decide which direction to move stencile...

			if( (f0 < f1) and (f1 <= f2) )
			{
				/* min to left */

				moveLeft(f);
		
			}
			else if( (f0 >= f1) and (f1 > f2) )
			{
				/* min to right */

				moveRight(f);

			}
			else if(  (f0 > f1) and (f1 == f2) )
			{
				/* min bracketed or to right? */

				// Move upper bound only ...

				alpha2 += delta;
				f2 = f(alpha2);

			}
			else if( (f0 == f1) and (f1 < f2) )
			{
				/* min bracketed or to left? */

				// Refine stencle and move mid-point to left...

				alpha0 -= delta;
				f0 = f(alpha0);
				
			}
			else if( (f0 < f1) and (f1 > f2) )
			{
				/* bracketed maximum => multiple minima */
				return MULTIPLEMIN;
			}
			else if( (f0 == f1) and (f1 == f2) )
			{
				/* found "flat spot" */
				
				// Move in preferred direction...

				if(dir < 0.0) 
					moveLeft(f);
				else
					moveRight(f);
			
			}

		}

		/* optimimum was not bracketd */

		return NOMIN;
	}

private:

	// Step size
	Real delta;
	
	// Stencil values
	Real alpha0, alpha1, alpha2;

	Real f0, f1, f2;

	// Preferred move direction
	Real dir;

	// Search limits
	Real alpha_min, alpha_max;

	// Moves stencil left
	void moveLeft(CostFunction& f)
	{
		alpha2 = alpha1;
		f2 = f1;

		alpha1 = alpha0;
		f1 = f0;

		alpha0 -= delta;
		f0 = f(alpha0);
	
		dir = -1.0;

	}

	// Moves stencil right
	void moveRight(CostFunction& f)
	{

		alpha0 = alpha1;
		f0 = f1;

		alpha1 = alpha2;
		f1 = f2;

		alpha2 += delta;
		f2 = f(alpha2);
			
		dir = 1.0;

	}

};

}}//::numlib::optimization

#endif
