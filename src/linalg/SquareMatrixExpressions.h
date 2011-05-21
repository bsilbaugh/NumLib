/*! \file SquareMatrixExpressions.h
 *  \brief Operator overloads for SquareMatrix
 *
 *  \todo Clean-up of matrix-vector production function. Using
 *  friend for SquareMatrix but not Vector; would be nice to
 *  be more consistent in usage (or non usage) of friend. In the
 *  case of SquareMatrix, is friend really needed?
 *
 *  \todo Consider reimplementing Vector to use raw C array instead
 *  of Array1D. This will allow forwarding of matrix-vector operations
 *  to LAPACK.
 */

#ifndef SQUARE_MATRIX_OVERLOADS_H
#define SQUARE_MATRIX_OVERLOADS_H

#include "Vector.h"
#include "SquareMatrix.h"

namespace numlib{ namespace linalg{

template<class T> inline
SquareMatrix<T> operator*(const SquareMatrix<T>& a, const T& c)
{
	SquareMatrix<T> b(a);
	return b *= c;
}

template<class T> inline
SquareMatrix<T> operator*(const T&c, const SquareMatrix<T>& a)
{
	return a*c;
}

template<class T> inline
SquareMatrix<T> operator/(const SquareMatrix<T>& a, const T& c)
{
	SquareMatrix<T> b(a);
	return b /= c;
}

template<class T> inline
SquareMatrix<T> operator+(const SquareMatrix<T>& a, const SquareMatrix<T>& b)
{
	SquareMatrix<T> c(a);
	return c += b;
}

template<class T> inline
SquareMatrix<T> operator-(const SquareMatrix<T>& a, const SquareMatrix<T>& b)
{
	SquareMatrix<T> c(a);
	return c -= b;
}

template<class T>
SquareMatrix<T> prod(const SquareMatrix<T>& a, const SquareMatrix<T>&b)
{
	ASSERT( a.size() == b.size() );
	const Size dim = a.size();
	SquareMatrix<T> c(dim);
	T val;
	for(Index j=0; j<dim; ++j)
	{
		for(Index i=0; i<dim; ++i)
		{
			val = T(0);
			for(Index k=0; k<dim; ++k)
				val += a(i,k)*b(k,j);
			c(i,j) = val;
		}
	}
	return c;
}

template<class T>
Vector<T> prod(const SquareMatrix<T>& a, const Vector<T>& u)
{
	ASSERT( a.size() == u.size() );
	const Size dim = u.size();
	Vector<T> v(dim);
	T val;
	for(Index i=0; i<dim; ++i)
	{
		val = T(0);
		for(Index j=0; j<dim; ++j)
			val += a(i,j)*u(j);
		v(i) = val;
	}
	return v;
}

}}//::numlib::linalg

#endif
