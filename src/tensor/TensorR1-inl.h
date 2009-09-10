/*! \file TensorR1-inl.h
 *  \brief Implimentation of inline functions for TensorR1
 */

namespace numlib{ namespace tensor{

inline
TensorR1::TensorR1():x(0.0),y(0.0),z(0.0)
{
}

inline
TensorR1::TensorR1(Real x_, Real y_, Real z_): x(x_), y(y_), z(z_)
{
}

inline
Real & TensorR1::operator()(Index i)
{
	switch(i)
	{
		case 1: 
			return x;
		case 2: 
			return y;
		case 3: 
			return z;
		default:
			throw IndexError();
	}
}

inline
Real TensorR1::operator()(Index i) const
{
	switch(i)
	{
		case 1: 
			return x;
		case 2: 
			return y;
		case 3: 
			return z;
		default:
			throw IndexError();
	}
}

inline
TensorR1 & TensorR1::zero()
{
	x = y = z = 0.0;
	return *this;
}

inline
TensorR1 & TensorR1::operator+=(const TensorR1 & u)
{
	x += u.x;
	y += u.y;
	z += u.z;
	return *this;
}

inline
TensorR1 & TensorR1::operator-=(const TensorR1 & u)
{
	x -= u.x;
	y -= u.y;
	z -= u.z;
	return *this;
}

inline
TensorR1 & TensorR1::operator*=(const Real a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}

inline
TensorR1 & TensorR1::operator/=(const Real a)
{
	if( a == 0.0 ) throw DivisionByZero();
	x /= a;
	y /= a;
	z /= a;
	return *this;
}

inline
TensorR1 operator+(const TensorR1 & u, const TensorR1 & v)
{
	TensorR1 w(u);
	w += v;
	return w;
}

inline
TensorR1 operator-(const TensorR1 & u, const TensorR1 & v)
{
	TensorR1 w(u);
	w -= v;
	return w;
}

inline
TensorR1 operator*(const Real & a, const TensorR1 & u)
{
	TensorR1 w(u);
	w *= a;
	return w;
}

inline
TensorR1 operator*(const TensorR1 & u, const Real & a)
{
	TensorR1 w(u);
	w *= a;
	return w;
}

inline
TensorR1 operator/(const TensorR1 & u, const Real & a)
{
	if( a == 0.0) throw DivisionByZero();
	TensorR1 w(u);
	w /= a;
	return w;
}

inline
Real dot(const TensorR1 & u, const TensorR1 & v)
{
	return u.x*v.x + u.y*v.y + u.z*v.z;
}

inline
TensorR1 cross(const TensorR1 & u, const TensorR1 & v)
{
	Real w1, w2, w3;

	w1 =  u.y*v.z - u.z*v.y;
	w2 = -u.x*v.z + u.z*v.x;
	w3 =  u.x*v.y - u.y*v.x;

	return TensorR1(w1, w2, w3);
}

inline
Real norm(const TensorR1 & u)
{
	return std::sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
}

inline
std::ostream & operator<<(std::ostream & os, const TensorR1 & u)
{
	os<<std::scientific<<"( "<<u.x<<", "<<u.y<<", "<<u.z<<" )";
	return os;
}

}} //::numlib::tensor
