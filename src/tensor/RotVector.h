/*! \file RotVector.h
 *  \brief Definition of the rotation vector and associated non-member functions
 */

#ifndef ROTVECTOR_H
#define ROTVECTOR_H

#include "TensorR1.h"

namespace numlib{ namespace tensor{

//! Rotation vector class
/*!
 *	This new type was introduced to faciliate overloading of functions
 *	related to finite-rotations. For example, the function Rot( ... )
 *	can be defined to compute the rotation tensor for a wide family of 
 *	rotation parameter vectors such as the rotation vector, 
 *	euler paremeters, quanternions, etc. The appropriate implementation
 *	of Rot(...) is then chosen by the compiler at compile time base on the
 *	argument type. This also means that a dynamics library can implement
 *	the rotation parameter vector as a generic concept; the final decision
 *	as to which rotation paramters to use can be defined through a simple
 *	typedef; e.g. 
 *
 *	  typedef RotVector RotParamVector;
 *
 *	and then later switch to, say, Euler parameters by replacing the above
 *	with
 *
 *	  typedef EulerParameters RotParamVector;
 *
 *	The expectation is that the choice of rotation parameters used by 
 *	another library or program will be known at compile time. Thus, the 
 *	static polymorphism described here should be an acceptable trade 
 *	between flexibility and run-time performance.
 *
 *	Note that a conversion from TensorR1 to RotVector is not defined. This
 *	is to avoid the possibility of another rotation vector being erroneously 
 *	typecast to RotVector via the common parent class TensorR1.
 */
class RotVector: public TensorR1
{
public:

	 //! Initializes rotation vector with provided Cartesian components
	 RotVector(Real x1=0.0, Real x2=0.0, Real x3=0.0);

	 virtual 
	 ~RotVector();

};

inline
RotVector operator+(const RotVector & u, const RotVector & v)
{
	 RotVector tmp(u);
	 tmp += v;
	 return tmp;
}

inline
RotVector operator-(const RotVector & u, const RotVector & v)
{
	 RotVector tmp(u);
	 tmp -= v;
	 return tmp;
}

inline
RotVector operator*(const RotVector & u, Real c)
{
	 RotVector tmp(u);
	 tmp *= c;
	 return tmp;
}

inline
RotVector operator*(Real c, const RotVector & u)
{
	 RotVector tmp(u);
	 tmp *= c;
	 return tmp;
}

inline
RotVector operator/(const RotVector & u, Real c)
{
	 RotVector tmp(u);
	 tmp /= c;
	 return tmp;
}

}} //::numlib::tensor

#endif
