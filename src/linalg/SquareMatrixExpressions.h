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

#ifndef SQUARE_MATRIX_EXPRESSION_H
#define SQUARE_MATRIX_EXPRESSION_H

#include "Vector.h"
#include "SquareMatrix.h"
#include "lapack_wrapper.h"

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

//! Directly solves [A]{x} = {b} where [A] is a dense square matrix
/*!
 *	Solves [A]{x} = {b} using the LU decomposition. The argument 'a' is
 *	the square coefficient matrix [A]. Upon input 'u' is the the 
 *	right-hand-side vector {b}; upon output 'u' is the solution vector
 *	{x}. This is intended as a high-level (i.e. quick-and-dirty) function
 *	for solving dense linear systems.
 *
 *	This function assumes only one right-hand-side vector. The underlying
 *	LAPACK subroutine DGESV does allow multiple right-hand-sides. If this
 *	is needed, use/create a solve function which exposes this functionality
 *	or use/create a lower level solver which treats LU factorization as
 *	an separate pre-processing step.
 *
 *	Note that a temporary work matrix is created to hold the LU factored
 *	[A] matrix (so as to preserve the original [A]). If you're solving a
 *	really big problem use a lower level solver which allows in-place
 *	modification of [A].
 */
template<class T>
void solve(const SquareMatrix<T>& a, Vector<T>& u)
{
	throw NumLibError("solve function not implemented; only implemented for Real matricies");
}

//! Specialization of template<class T> solve function for T=Real.
/*!
 *  This forwards the solution of [A]{x} = {b} to the LAPACK subroutine DGESV.
 *
 *  \todo Look into making this a friend function so that the internal
 *  data of SquareMatrix and Vector can be passed directly to the
 *  fortran LAPACK routine.
 */
template<>
void solve<Real>(const SquareMatrix<Real>& a, Vector<Real>& u)
{
	ASSERT( a.size() == u.size() );

	Size nrhs = 1;
	Size n = a.size();

	Real* a_data = new Real[n*n];
	for(Index j=0; j<n; ++j)
		for(Index i=0; i<n; ++i)
			a_data[i+j*n] = a(i,j);

	Real* u_data = new Real[n];
	for(Index i=0; i<n; ++i)
		u_data[i] = u(i);

	Int* p_data = new Int[n];

	Int info = lapack_dgesv(n, nrhs, a_data, n, p_data, u_data, n);

	DEBUG_PRINT_VAR( info );

	for(Index i=0; i<n; ++i)
		u(i) = u_data[i];

	delete[] a_data;
	delete[] u_data;
	delete[] p_data;

	if(info!=0)
		throw NumLibError("Failed to solve linear system");
}

}}//::numlib::linalg

#endif
