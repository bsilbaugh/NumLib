/*! \file TensorR2.cpp
 *  \brief Implimentation of TensorR2 class
 */

#include "TensorR2.h"

namespace numlib{ namespace tensor{

TensorR2::TensorR2():
	a11(0.0),a12(0.0),a13(0.0),
	a21(0.0),a22(0.0),a23(0.0),
	a31(0.0),a32(0.0),a33(0.0),
	indexMap(0)
{
	initIndexMap();
}

TensorR2::TensorR2(Real t11, Real t12, Real t13,
			       Real t21, Real t22, Real t23,
			       Real t31, Real t32, Real t33):
	a11(t11), a12(t12), a13(t13),
	a21(t21), a22(t22), a23(t23),
	a31(t31), a32(t32), a33(t33)

{
	initIndexMap();
}

TensorR2::TensorR2(const TensorR2 & other)
{
	copy(other);
	initIndexMap();
}

TensorR2::~TensorR2()
{
	delIndexMap();
}

TensorR2 & TensorR2::operator=(const TensorR2 & other)
{
	// Note: index map already points to data of this; only to to copy
	if(&other!=this)
		copy(other);
	return *this;
}

TensorR2 & TensorR2::operator+=(const TensorR2 & other)
{
	a11 += other.a11;
	a12 += other.a12;
	a13 += other.a13;

	a21 += other.a21;
	a22 += other.a22;
	a23 += other.a23;

	a31 += other.a31;
	a32 += other.a32;
	a33 += other.a33;

	return *this;
}

TensorR2 & TensorR2::operator-=(const TensorR2 & other)
{
	a11 -= other.a11;
	a12 -= other.a12;
	a13 -= other.a13;

	a21 -= other.a21;
	a22 -= other.a22;
	a23 -= other.a23;

	a31 -= other.a31;
	a32 -= other.a32;
	a33 -= other.a33;

	return *this;
}

TensorR2 & TensorR2::operator*=(Real a)
{
	a11 *= a;
	a12 *= a;
	a13 *= a;

	a21 *= a;
	a22 *= a;
	a23 *= a;

	a31 *= a;
	a32 *= a;
	a33 *= a;

	return *this;
}

TensorR2 & TensorR2::operator/=(Real a)
{
	if(a == 0.0) throw DivisionByZero();

	a11 /= a;
	a12 /= a;
	a13 /= a;

	a21 /= a;
	a22 /= a;
	a23 /= a;

	a31 /= a;
	a32 /= a;
	a33 /= a;

	return *this;
}

TensorR2 dot(const TensorR2 & t1, const TensorR2 & t2)
{
	Real r11, r12, r13;
	Real r21, r22, r23;
	Real r31, r32, r33;

	r11 = t1.a11 * t2.a11 + t1.a12 * t2.a21 + t1.a13 * t2.a31;
	r12 = t1.a11 * t2.a12 + t1.a12 * t2.a22 + t1.a13 * t2.a32;
	r13 = t1.a11 * t2.a13 + t1.a12 * t2.a23 + t1.a13 * t2.a33;

	r21 = t1.a21 * t2.a11 + t1.a22 * t2.a21 + t1.a23 * t2.a31;
	r22 = t1.a21 * t2.a12 + t1.a22 * t2.a22 + t1.a23 * t2.a32;
	r23 = t1.a21 * t2.a13 + t1.a22 * t2.a23 + t1.a23 * t2.a33;

	r31 = t1.a31 * t2.a11 + t1.a32 * t2.a21 + t1.a33 * t2.a31;
	r32 = t1.a31 * t2.a12 + t1.a32 * t2.a22 + t1.a33 * t2.a32;
	r33 = t1.a31 * t2.a13 + t1.a32 * t2.a23 + t1.a33 * t2.a33;

	return TensorR2(r11, r12, r13, r21, r22, r23, r31, r32, r33);
}

std::ostream & operator<<(std::ostream & os, const TensorR2 & t)
{
	os<<"\n\t[ "<<t.a11<<", "<<t.a12<<", "<<t.a13<<" ]"
	  <<"\n\t[ "<<t.a21<<", "<<t.a22<<", "<<t.a23<<" ]"
	  <<"\n\t[ "<<t.a31<<", "<<t.a32<<", "<<t.a33<<" ]"
	  <<std::endl;
	return os;
}

void TensorR2::copy(const TensorR2 & other)
{
	a11 = other.a11;
	a12 = other.a12;
	a13 = other.a13;

	a21 = other.a21;
	a22 = other.a22;
	a23 = other.a23;

	a31 = other.a31;
	a32 = other.a32;
	a33 = other.a33;
}

void TensorR2::initIndexMap()
{
	indexMap = new Real**[3];
	indexMap[0] = new Real*[3];
	indexMap[1] = new Real*[3];
	indexMap[2] = new Real*[3];

	indexMap[0][0] = &a11;
	indexMap[0][1] = &a12;
	indexMap[0][2] = &a13;

	indexMap[1][0] = &a21;
	indexMap[1][1] = &a22;
	indexMap[1][2] = &a23;

	indexMap[2][0] = &a31;
	indexMap[2][1] = &a32;
	indexMap[2][2] = &a33;
}

void TensorR2::delIndexMap()
{
	delete[] indexMap[2];
	delete[] indexMap[1];
	delete[] indexMap[0];
	delete[] indexMap;
	indexMap = 0;
}

}} //::numlib::tensor
