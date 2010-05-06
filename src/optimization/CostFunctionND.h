/*! \file CostFunctionND.h
 *  \brief CostFunctionND template definition.
 */

#ifndef COST_FUNCTION_ND_H
#define COST_FUNCTION_ND_H

#include "../base/numlib-config.h"
#include "../base/nocopy.h"

namespace numlib{ namespace optimization{

//! Model of a generic n-dimensional cost function
/*!
 *  Multi-dimensional version of CostFunction1D. Template parameters F and 
 *  GradF should be function pointers (or member function pointers) to
 *  user defined cost function and gradient function, respectively. In
 *  principle, F and GradF could be object classes (possibly the same)
 *  provided the call operators are properly overloaded. Use of object
 *  classes in lieu of function pointers will result in the object
 *  passed to the contructor being copied; in most situations this is
 *  undesirable. The expectation is that functions pointers will be
 *  used.
 *
 *  Note that the user does not have to use this template. Since all NumLib ND
 *  optimizers take the cost function type as a template arguement, the user
 *  simply needs to create a class which posses the same interface.
 */
template<class F, class GradF, class V >
class CostFunctionND
{
public:

	typedef V VectorType;

	CostFunctionND(F& f_, GradF& gradf_, Size n_):
		f(f_), gradf(gradf_), n(n_)
	{}

	Size size() const {return n;}

	Real operator()(const V& x) {return f(x);}

	void operator()(const V& x, V& grad) { gradf(x, grad);}

private:

	DISALLOW_COPY_AND_ASSIGN( CostFunctionND );

	F f;

	GradF gradf;

	Size n;

};

}}//::numlib::optimization

#endif
