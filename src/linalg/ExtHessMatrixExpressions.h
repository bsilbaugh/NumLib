/*! \file ExtHessMatrixExpressions.h */

#ifndef EXT_HESS_MATRIX_EXPRESSIONS_H
#define EXT_HESS_MATRIX_EXPRESSIONS_H

#include "ExtHessMatrix.h"

namespace numlib{ namespace linalg{
	
	/*** HessMatrix-Scalar operations ***/

	/*** HessMatrix-Vector operations ***/

//! Computes the left Extended Hessenberg matrix vector product
/*!
 *  \todo This could be made more efficient if friend of Hessenberg.
 */
template<class T>
Vector<T> prod(const ExtHessMatrix<T> & a, const Vector<T> & u)
{

	 /* This could be more efficient */

	 Size n = a.size1();
	 Size m = a.size2();

	 Vector<T> v(n);
	 v.zero();

	 for(Index j=0; j<m; ++j)
		  for(Index i=0; i<j+2; ++i)
			   v(i) += a(i,j)*u(j);

	 return v;
}

//! Directly solves min J(x), where J(x) = ||{b} - [H]{x}||_2
/*!
 *  On input, 'hess' is the upper extented Hessinburg matrix [H] and 'x' is the RHS
 *  vector {b}. On output, 'hess' contains the upper triangular matrix
 *  [R] = [Q][H], where [Q] is the product of a sequence of plane rotations,
 *  and 'x' contains the minimizer of J(x) in first m-1 elements, and the
 *  2-norm of the residual in the last element.
 *
 *  See Iterative Methods for Sparse Linear Systems by Yousef Saad.
 */
template<class T>
void solveInPlaceLeastSquare(HessMatrix<T>& hess, Vector<T>& x)
{
	// Get problem size...
	const Size m = hess.size1();
	const Size n = hess.size2();

	// Check dimensions...
	ASSERT( x.size() == m );
	ASSERT( m == n + 1 );

	// Some temp work var...
	Real ta, tb, tc;

	// Transform to upper triangular matrix using plane rotations...
	for(Index i=0; i<n; ++i)
	{
		// Compute ith rotation ...
		ta = hess(i,i);
		tb = hess(i+1,i);
		tc = sqrt( ta*ta + tb*tb );
		const Real s = tb/tc;
		const Real c = ta/tc;

		// Apply ith rotation to coef matrix...
		for(Index j=i; j<n; ++j)
		{
			ta = hess(i,j);
			tb = hess(i+1,j);
			hess(i,j)   =  c*ta + s*tb;
			hess(i+1,j) = -s*ta + c*tb; /* should be zero when j == i */
		}

		// Apply ith rotation to RHS vector...
		ta = x(i);
		tb = x(i+1);
		x(i)   =  c*ta + s*tb;
		x(i+1) = -s*ta + c*tb; /* contains 2-norm of res when i = n-1 */
	}

	// Solve upper triangular system...
	for(Index p=n; p>0; --p)
	{
		const Index i = p-1;

		ta = x(i);
		for(Index j=i+1; j<n; ++j)
		{
			ta -= hess(i,j)*x(j);
		}
		x(i) = ta/hess(i,i);
	}

}

}}//::numlib::linalg

#endif
