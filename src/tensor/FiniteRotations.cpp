
#include "FiniteRotations.h"

namespace numlib{ namespace tensor{

TensorR2 rot(const RotVector & rv)
{
	using std::sin;

	// Rotation angle about the rotation axis aligned with rv
	Real theta = norm(rv);

	// Check for zero rotation angle -- if zero return identity
	if(theta == 0.0) return identity();

	Real theta2 = 0.5*theta;

	Real c1 = sin(theta)/theta;
	Real c2 = sin(theta2)/theta2;

	TensorR2 s = skew(rv);

	TensorR2 tmp = identity();
	tmp += c1*s;
	tmp += (0.5*c2*c2)*dot(s,s);

	return tmp;
}

TensorR2 rot(const ReferenceFrame & frame)
{
	TensorR1 e1 = frame(1);
	TensorR1 e2 = frame(2);
	TensorR1 e3 = frame(3);

	Real a11 = e1(1); 
	Real a12 = e2(1); 
	Real a13 = e3(1);

	Real a21 = e1(2); 
	Real a22 = e2(2); 
	Real a23 = e3(2);

	Real a31 = e1(3); 
	Real a32 = e2(3); 
	Real a33 = e3(3);

	return TensorR2(a11, a12, a13, a21, a22, a23, a31, a32, a33);
}

TensorR2 tanMap(const RotVector & rv)
{
	using std::sin;

	Real theta = norm(rv);

	if(theta == 0.0) return identity();

	Real theta2 = 0.5*theta;

	TensorR1 e = rv/theta;

	TensorR2 ee = dyad(e,e);

	TensorR2 sk = skew(rv);

	Real c1 = sin(theta)/theta;

	Real c2 = sin(theta2)/theta2;

	TensorR2 res = identity();
	res *= c1;
	res += (1.0 - c1)*ee;
	res -= (0.5*c2*c2)*sk;

	return res;
}

TensorR2 tanMapDer(const RotVector & rv, const RotVector & delta_rv)
{

	using std::sin;
	using std::cos;

	Real theta = norm(rv);

	if(theta == 0.0) return -0.5*skew(delta_rv);

	Real theta2 = 0.5*theta;

	TensorR1 e = rv/theta;
	TensorR2 ee = dyad(e,e);

	Real c1 = sin(theta)/theta;
	Real c2 = sin(theta2)/theta2;
	Real c3 = cos(theta);
	Real c4 = dot(e, delta_rv);
	Real c5 = c4/theta;

	Real c2c2 = c2*c2;

	TensorR2 e_delta_rv = dyad(e, delta_rv);
	TensorR2 delta_rv_e = transpose(e_delta_rv);

	TensorR2 tmp = identity();
	tmp *= (c3 - c1)*c5;
	tmp += (1.0 - c1)*(delta_rv_e + e_delta_rv)/theta;
	tmp += (3.0*c1 - c3 - 2.0)*c5*ee;
	tmp += (c2c2 - c1)*c5*skew(rv);
	tmp -= 0.5*c2c2*skew(delta_rv);

	return tmp;

}

TensorR1 angAcc(const RotVector & rv, const RotVector & rv_dot, const RotVector & rv_ddot)
{
	TensorR1 tmp = dot(tanMapDer(rv, rv_dot), rv_dot);
	tmp += dot(tanMap(rv), rv_ddot);
	return tmp;
}

}} //::numlib::tensor
