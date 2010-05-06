/*! \file LineRestriction.h
 *  \breif LineRestriction template definition
 */

#ifndef LINE_RESTRICTION_H
#define LINE_RESTRICTION_H

#include "CostFunctionND.h"

namespace numlib{ namespace optimization{

//! Models the restriction of a multi-variable cost function to a 1D sub-domain
/*!
 *  This serves as an adaptor of a multi-variable cost function (e.g. 
 *  CostFunctionND) which allows line searches to be performed by NumLib 1D 
 *  optimizers. 
 *
 *  This simple adaptor maps a scalar argument, alpha, to the 1-dimensional 
 *  subspace defined by the affine map x + alpha*s, where
 *  	
 *  	x := reference position in the n-dimensional design space
 *  	s := search direction in the n-dimensional design space
 *
 */
template<class CostFunction >
class LineRestriction
{
public:

	typedef typename CostFunction::VectorType VectorType;

	// Constructs the restriction of F to a line
	/*!
	 *  f_ := underlying multi-variable cost function (an instance of 
	 *        CostFunctionND)
	 *
	 *  pos := reference point in n-dimensional design space
	 *  dir := search direction in n-dimensional design space
	 *
	 *  WARNING: Only the references to x and s are stored (x and s are not
	 *  copied)! Be mindful that updates to x and s outside of this class will 
	 *  automatically be reflected here. For most multi-dimensional optimization 
	 *  algorithms this is actually desirable since the 'outer' routine usually 
	 *  just updates x and s then calls the 1D optimizer to perform the line 
	 *  search.
	 */
	LineRestriction(CostFunction& f_, const VectorType& pos, const VectorType& dir):
		f(f_), x(pos), s(dir)
	{}

	// Evaluates the restriction of f to the line x + alpha*s
	Real operator()(Real alpha) {return f(x + alpha*s);}

private:

	DISALLOW_COPY_AND_ASSIGN( LineRestriction );

	// Underlying multi-variable cost function; e.g. CostFunctionND
	CostFunction& f;

	// Reference to reference position vector
	const VectorType& x;

	// Reference to search direction vector
	const VectorType& s;

};

}}//::numlib::optimization

#endif
