/*! \file EulerParameterVector.cpp
 */

#include "EulerParameterVector.h"

namespace numlib{ namespace tensor{

EulerParameterVector::EulerParameterVector(Real q1_, Real q2_, Real q3_, Real q4_):
	 q1(q1_),
	 q2(q2_),
	 q3(q3_),
	 q4(q4_)
{
}

EulerParameterVector::EulerParameterVector(const TensorR2 & r)
{
	 using std::sqrt;

	 Real r12 = r(1,2);
	 Real r21 = r(2,1);

	 Real r13 = r(1,3);
	 Real r31 = r(3,1);

	 Real r23 = r(2,3);
	 Real r32 = r(3,2);

	 q4 = sqrt(0.25*(trace(r) + 1.0));

	 Real q44 = 4.0*q4;

	 q1 = (r32 - r23)/q44;
	 q2 = (r13 - r31)/q44;
	 q3 = (r21 - r12)/q44;
}

EulerParameterVector::EulerParameterVector(const EulerParameterVector & other):
	 q1(other.q1),
	 q2(other.q2),
	 q3(other.q3),
	 q4(other.q4)
{
}

EulerParameterVector::~EulerParameterVector()
{
	 /* nothing to delete */
}

EulerParameterVector & EulerParameterVector::operator=(const EulerParameterVector & other)
{
	 if(&other != this)
		  return *this;

	 q1 = other.q1;
	 q2 = other.q2;
	 q3 = other.q3;
	 q4 = other.q4;
	 
}

Real & EulerParameterVector::operator()(Index i)
{
	 switch(i)
	 {
	 case 1:
		  return q1;
	 case 2:
		  return q2;
	 case 3:
		  return q3;
	 case 4:
		  return q4;
	 }
}

const Real & EulerParameterVector::operator()(Index i) const
{
	 switch(i)
	 {
	 case 1:
		  return q1;
	 case 2:
		  return q2;
	 case 3:
		  return q3;
	 case 4:
		  return q4;
	 }
}

}}//::numlib::tensor
