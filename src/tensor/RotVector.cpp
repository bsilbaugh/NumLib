
#include "RotVector.h"

namespace numlib{ namespace tensor{

RotVector::RotVector(const TensorR2 & rotTensor)
{
	using std::sin;
	using std::acos;

	Real a11 = rotTensor(1,1);
	Real a12 = rotTensor(2,1);
	Real a13 = rotTensor(3,1);

	Real a21 = rotTensor(1,2);
	Real a22 = rotTensor(2,2);
	Real a23 = rotTensor(3,2);

	Real a31 = rotTensor(1,3);
	Real a32 = rotTensor(2,3);
	Real a33 = rotTensor(3,3);

	Real theta = acos( 0.5*(a11 + a22 + a33 - 1.0) );

	Real two_sine_theta = 2.0*sin(theta);

	x = (a23 - a32)/two_sine_theta;
	y = (a31 - a13)/two_sine_theta;
	z = (a12 - a21)/two_sine_theta;

	x *= theta;
	y *= theta;
	z *= theta;

}

}} //::numlib::tensor
