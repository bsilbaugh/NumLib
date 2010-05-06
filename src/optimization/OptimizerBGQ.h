/*! \file OptimizerBGQ.h
 *  \brief OptimizerBGQ template definition
 */

#ifndef OPTIMIZER_BGQ_H
#define OPTIMIZER_BGQ_H

#include "BracketFinder.h"
#include "GoldenSection.h"
#include "QuadraticInterp.h"

namespace numlib{ namespace optimization{

//! 1-dimensional unconstrained optimizer
/*!
 *  This solves 1-dimensional unconstrained optimization problems by 
 *  sequentially applying the following methods:
 *  1. Bracket method: used to find upper and lower bounds of a minimum
 *  2. Golden section search: used to reduce the bounds determined by bracket
 *     method and provide rough estimate of the minimum
 *  3. Quadratic interpolation: used to determine a refined estimate for the 
 *     optimum
 *
 *  The foregoing approach is fairly standard and has been found to be quite 
 *  robust for most problems. Note that all of the above techniques are zeroth 
 *  order; derivative information is not required. In principle, one could 
 *  replace step 3 above with Newton's method if derivative information were 
 *  available. However, Newton's method essentially assumes a quadratic model; 
 *  thus overall performance may not be much better than the quadratic 
 *  interpolation.
 *
 *  The template argument CostFunction may be any callable class or
 *  function pointer
 */
template<class CostFunction>
class OptimizerBGQ
{
public:

	//! Initializes optimizer parameters
	/*!
	 *  Constructor arguments:
	 *	- bf_step := step size used by BracketMethod
	 *	- gs_reduction := interval reduction ratio used to terminate GoldenSection
	 *	- qf_tol := tolerance (max change in f) used to terminate QuadraticInterp
	 */
	OptimizerBGQ(Real bf_step=1.0, Real gs_reduction=0.1, Real qf_tol=5.0E-3):
		bracketFinder(bf_step),
		goldenSection(gs_reduction),
		quadraticInterp(qf_tol)
	{}

	//! Sets step size used by BracketMethod
	void bracketStepSize(Real bf_step) {bracketFinder.stepSize(bf_step);}

	//! Returns step size used by BracketMethod
	Real bracketStepSize() const {return bracketFinder.stepSize();}

	//! Sets interval reduction ratio used to terminate GoldenSection
	void reductionRatio(Real gs_reduction) {goldenSection.reductionRatio(gs_reduction);}

	//! Returns interval reduction ratio used to terminate GoldenSection
	Real reductionRatio() const {return goldenSection.reductionRatio();}

	//! Sets tolerance used to terminate QuadraticInterp
	void tolerance(Real qf_tol) {quadraticInterp.tolerance(qf_tol);}

	//! Returns tolerance used to terminate QuadraticInterp
	Real tolerance() const {return quadraticInterp.tolerance();}

	//! Finds a minimum of the cost function 'f'
	ErrorCode minimize(CostFunction& f, Minimum1D& min)
	{

		ErrorCode code;

		// Attempt to bracket a minimum...

		code = bracketFinder.minimize(f, min);

		if(code != SUCCESS) return code;

		// Reduce search interval and get rough estimate for optimum...

		code = goldenSection.minimize(f, min);

		if(code != SUCCESS) return code;

		// Refine optimum estimate...

		code = quadraticInterp.minimize(f, min);

		return code;

	}

private:

	BracketFinder<CostFunction> bracketFinder;

	GoldenSection<CostFunction> goldenSection;

	QuadraticInterp<CostFunction> quadraticInterp;

};

}}//::numlib::optimization

#endif
