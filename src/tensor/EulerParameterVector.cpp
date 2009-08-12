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
	 DEBUG_PRINT_VAR( q1 );
	 DEBUG_PRINT_VAR( q2 );
	 DEBUG_PRINT_VAR( q3 );
	 DEBUG_PRINT_VAR( q4 );
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

	 Real tr = trace(r);

	 ASSERT( tr > -1.0 );

	 q4 = sqrt(0.25*(tr + 1.0));

	 Real q44 = 4.0*q4;

	 q1 = (r32 - r23)/q44;
	 q2 = (r13 - r31)/q44;
	 q3 = (r21 - r12)/q44;

	 DEBUG_PRINT_VAR( q1 );
	 DEBUG_PRINT_VAR( q2 );
	 DEBUG_PRINT_VAR( q3 );
	 DEBUG_PRINT_VAR( q4 );
}

EulerParameterVector::EulerParameterVector(const TensorR1 & e, Real theta)
{
	 using std::cos;
	 using std::sin;

	 Real theta2 = 0.5*theta;
	 Real c = cos(theta2);
	 Real s = sin(theta2);

	 q4 = c;
	 q1 = e(1)*s;
	 q2 = e(2)*s;
	 q3 = e(3)*s;
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
	 if(&other == this)
		  return *this;

	 q1 = other.q1;
	 q2 = other.q2;
	 q3 = other.q3;
	 q4 = other.q4;

	 return *this;
	 
}

Real EulerParameterVector::rotationAngle() const
{
	 using std::acos;

	 DEBUG_PRINT_VAR( q4 );

	 return 2.0*acos(q4);
}

TensorR1 EulerParameterVector::rotationAxis() const
{
	 using std::sin;

	 Real s = sqrt(q1*q1 + q2*q2 + q3*q3);

	 if( s < 1.0E-12 ) return TensorR1(0,0,0);

	 DEBUG_PRINT_VAR( s );
	 DEBUG_PRINT_VAR( q1 );
	 DEBUG_PRINT_VAR( q2 );
	 DEBUG_PRINT_VAR( q3 );

	 Real e1 = q1/s;
	 Real e2 = q2/s;
	 Real e3 = q3/s;

	 DEBUG_PRINT_VAR( e1*e1 + e2*e2 + e3*e3 );
	 ASSERT( fabs(e1*e1 + e2*e2 + e3*e3 - 1.0) < 1.0E-10 );

	 return TensorR1(e1, e2, e3);
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

std::ostream & operator<<(std::ostream & os, const EulerParameterVector & ep)
{
	 os<<std::scientific
	   <<"( "<<ep.q1
	   <<", "<<ep.q2
	   <<", "<<ep.q3
	   <<", "<<ep.q4
	   <<" )";
}

}}//::numlib::tensor
