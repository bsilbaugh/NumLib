/*! \file TensorR2-inl.h
 *  \brief Inlined member functions and associated operators
 */

namespace numlib{ namespace tensor{

inline
Real & TensorR2::operator()(Index i, Index j)
{
	if( (i < 1) or (i > 3) or (j < 1) or (j > 3)) throw IndexError();
	return *(indexMap[i-1][j-1]);
}

inline
Real TensorR2::operator()(Index i, Index j) const
{
	if( (i < 1) or (i > 3) or (j < 1) or (j > 3)) throw IndexError();
	return *(indexMap[i-1][j-1]);
}

inline
TensorR2 & TensorR2::zero()
{
	a11 = a12 = a13 = a21 = a22 = a23 = a31 = a32 = a33 = 0.0;
	return *this;
}

//! Creates the identity-3 tensor
inline
TensorR2 identity()
{
	return TensorR2(1.0, 0.0, 0.0,
			        0.0, 1.0, 0.0,
					0.0, 0.0, 1.0);
}

inline
TensorR2 operator+(const TensorR2 & t1, const TensorR2 & t2)
{
	TensorR2 res(t1);
	res += t2;
	return res;
}

inline
TensorR2 operator-(const TensorR2 & t1, const TensorR2 & t2)
{
	TensorR2 res(t1);
	res -= t2;
	return res;
}

inline
TensorR2 operator*(const TensorR2 & t, Real a)
{
	TensorR2 res(t);
	res *= a;
	return res;
}

inline
TensorR2 operator*(Real a, const TensorR2 & t)
{
	TensorR2 res(t);
	res *= a;
	return res;
}

inline
TensorR2 operator/(const TensorR2 & t, Real a)
{
	TensorR2 res(t);
	res /= a;
	return res;
}

inline
TensorR2 transpose(const TensorR2 & t)
{
	return TensorR2(t.a11, t.a21, t.a31,
			        t.a12, t.a22, t.a32,
					t.a13, t.a23, t.a33);
}

}} //::numlib::tensor
