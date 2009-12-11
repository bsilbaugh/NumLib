/*! \file HypTan.h
 */

#ifndef HYPTAN_H
#define HYPTAN_H

#include "../base/numlib-config.h"

namespace numlib{ namespace nnet{

class HypTan
{
public:

	//! Initializes parameters of hyperbolic tangent function, a*tanh(b*v)
	/*!
	 *  Default parameter values based on Haykin (2008).
	 */
	HypTan(Real a_=1.7159, Real b_=0.6666):a(a_),b(b_){}

	Real operator()(Real v) {return a*tanh(b*v);}

private:

	Real a;

	Real b;

};

}}//::numlib::nnet

#endif
