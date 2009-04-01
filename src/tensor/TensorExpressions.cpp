/*! \file TensorExpressions.cpp
 *  \brief Implimentation of tensor expressions
 */

#include "TensorExpressions.h"

namespace numlib{ namespace tensor{

TensorR1 dot(const TensorR2 & A, const TensorR1 & u)
{
	Real u1, u2, u3;
	Real v1, v2, v3;

	u1 = u.x;
	u2 = u.y;
	u3 = u.z;

	v1 = A.a11 * u1 + A.a12 * u2 + A.a13 * u3;
	v2 = A.a21 * u1 + A.a22 * u2 + A.a23 * u3;
	v3 = A.a31 * u1 + A.a32 * u2 + A.a33 * u3;

	return TensorR1(v1, v2, v3);
}

TensorR1 dot(const TensorR1 & u, const TensorR2 & A)
{
	Real u1, u2, u3;
	Real v1, v2, v3;

	u1 = u.x;
	u2 = u.y;
	u3 = u.z;

	v1 = u1* A.a11 + u2 * A.a21 + u3 * A.a31;
	v2 = u1* A.a12 + u2 * A.a22 + u3 * A.a32;
	v3 = u1* A.a13 + u2 * A.a23 + u3 * A.a33;

	return TensorR1(v1, v2, v3);
}

Real v_dot_A_dot_u(const TensorR1 & v, const TensorR2 & A, const TensorR1 & u)
{
	Real u1, u2, u3;
	Real v1, v2, v3;
	Real tmp;

	u1 = u.x;
	u2 = u.y;
	u3 = u.z;

	v1 = v.x;
	v2 = v.y;
	v3 = v.z;

	tmp  = v1 * (A.a11 * u1 + A.a12 * u2 + A.a13 * u3);
	tmp += v2 * (A.a21 * u1 + A.a22 * u2 + A.a23 * u3);
	tmp += v3 * (A.a31 * u1 + A.a32 * u2 + A.a33 * u3);

	return tmp;
}

}} //::numlib::tensor
