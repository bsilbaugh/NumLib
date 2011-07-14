/*! \file MatrixExpressions.h
 *  \brief Operator overloads for Matrix type.
 */

#ifndef MATRIX_EXPRESSIONS_H
#define MATRIX_EXPRESSIONS_H

namespace numlib{ namespace linalg{

template<class T> inline
Matrix<T> operator*(const Matrix<T> a, const T& c)
{
	Matrix<T> b(a);
	return b*= c;
}

template<class T> inline
Matrix<T> operator*(const T& c, const Matrix<T>& a)
{
	return a*c;
}

template<class T> inline
Matrix<T> operator/(const Matrix<T>& a, const T& c)
{
	Matrix<T> b(a);
	return b /= c;
}

template<class T> inline
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
	Matrix<T> c(a);
	return c += b;
}

template<class T> inline
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
{
	Matrix<T> c(a);
	return c -= b;
}

template<class T>
Matrix<T> prod(const Matrix<T>&a, const Matrix<T>& b)
{
	ASSERT( a.size2() == b.size1() );
	Matrix<T> c(a.size1(), b.size2() );
	for(Index i=0; i<c.size1(); ++i)
	{
		for(Index j=0; j<c.size2(); ++j)
		{
			T val(0);
			for(Index k=0; k<a.size2(); ++k)
				val += a(i,k)*b(k,j);
			c(i,j) = val;
		}
	}
	return c;
}

template<class T>
Vector<T> prod(const Matrix<T>& a, const Vector<T>& u)
{
	ASSERT( a.size2() == u.size() );
	Vector<T> v(a.size1());
	for(Index i=0; i<v.size(); ++i)
	{
		T val(0);
		for(Index j=0; j<a.size2(); ++j)
			val += a(i,j)*u(j);
		v(i) = val;
	}
	return v;
}

//! Implements inner product <u,A> = transpose(u)*A
template<class T>
Vector<T> prod(const Vector<T>& u, const Matrix<T>& a)
{
	ASSERT( u.size() == a.size1() );
	Vector<T> v(a.size2());
	for(Index j=0; j<v.size(); ++j)
	{
		T val(0);
		for(Index i=0; i<a.size1(); ++i)
			val += u(i)*a(i,j);
		v(j) = val;
	}
	return v;
}

}}//::numlib::linalg

#endif
