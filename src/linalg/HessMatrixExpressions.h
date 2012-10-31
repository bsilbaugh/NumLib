/*! \file HessMatrixExpressions.h
 */

#ifndef HESSMATRIXEXPRESSIONS_H
#define HESSMATRIXEXPRESSIONS_H

namespace numlib{ namespace linalg{

	/*** HessMatrix-Scalar operations ***/

	/*** HessMatrix-Vector operations ***/


//! Computes the left Hessenberg matrix vector product
/*!
 *  \todo This could be made more efficient if friend of Hessenberg.
 */
template<class T>
Vector<T> prod(const HessMatrix<T> & a, const Vector<T> & u)
{

	 /* This could be more efficient */

	 Size n = a.size1();
	 Size m = a.size2();
	 Vector<T> v(n);
	 v.zero();
	 for(Index j=0; j<m-1; ++j)
		  for(Index i=0; i<j+2; ++i)
			   v(i) += a(i,j)*u(j);
	 for(Index i=0; i<n; ++i)
		  v(i) += a(i,m-1)*u(m-1);

	 return v;
}

//! Computes the ``Doolittle'' LU factorization of [A]
/*!
 *  LU factorization is performed in place to minimize memory requirements
 *
 *  In ``Doolittle'' factorization, the 1's are on the main diagonal of
 *  the lower diagonal matrix.
 */
template<class T>
void factorLU(HessMatrix<T> & hess)
{
	 // Get problem size...

	 ASSERT( hess.size2() == hess.size1() );

	 Size n = hess.size2();

	 // Compute LU factorization...

	 T c;
	 for(Index i=1; i<n; ++i)
	 {

		  // Compute elements of [L] for ith row...

		  /* REMINDER: L_{i,i} = 1.0 and L_{i,j} = 0 for all 0 < j < i-1 */
	
		  c = hess(i,i-1)/hess(i-1,i-1);
		  hess(i,i-1) = c; // L_{i,i-1}

		  // Compute elements of [U] for ith row...

		  for(Index j=i; j<n; ++j) hess(i,j) -= c*hess(i-1,j);
	
	 }

}

//! Directly solves [A]{x} = {b} where [A] = [L][U] is (upper) Hessenberg
/*!
 *  Upon input, 'hessLU' is the LU factorization of an (upper) Hessenberg 
 *  coefficient matrix [A], and 'x' is the RHS vector {b}. Upon output, 
 *  'x' is overwritten with the solution vector {x}.
 *
 *  ``Doolittle'' LU factorization is assumed (1's on the diagonal of [L])
 */
template<class T>
void solveLU(const HessMatrix<T> & hessLU, Vector<T> & x)
{
	 // Get problem size...

	 ASSERT( hessLU.size1() == hessLU.size2() );
	 ASSERT( x.size() == hessLU.size1() );

	 Size n = hessLU.size2();

	 DEBUG_PRINT_VAR( n );

	 // Solve [L]{d} = {b} with {b} overwritten with {d}...
	 DEBUG_PRINT( "Solving lower system..." );
	 for(Index i = 1; i<n; ++i)
		  x(i) = x(i) - hessLU(i,i-1)*x(i-1);

	 // Solve [U]{x} = {d} with {d} overwritten with {x}...
	 DEBUG_PRINT( "Solving upper system..." );
	 T z;
	 Index im1;
	 x(n-1) /= hessLU(n-1,n-1);
	 for(Index i=n-1; i > 0; --i)
	 {
		  im1 = i-1;
		  z = 0;
		  for(Index j = i; j < n; ++j) z += hessLU(im1,j)*x(j);
		  x(im1) = (x(im1) - z)/hessLU(im1,im1);
	 }
}

//! Computes the LU factorization of [A] with row pivoting
/*!
 *  LU factorization is performed in place to minimize memory requirements.
 *  Row pivoting is used to improve numerical conditioning.
 *
 */
template<class T>
void factorLU(HessMatrix<T> & hess, Vector<Index> & p)
{
	 // Get problem size...

	 ASSERT( hess.size2() == hess.size1() );

	 Size n = hess.size2();

	 ASSERT( p.size() == n );

	 // Initialize pivot vector...

	 for(Index i=0; i<n; ++i)
		 p(i) = i;

	 // Compute LU factorization...

	 T c;
	 for(Index i=1; i<n; ++i)
	 {

		 // Pivot rows...

		 if( fabs(hess(p(i-1),i-1)) < fabs(hess(p(i),i-1)) )
		 {
			 Index im1 = p(i-1);
			 p(i-1) = p(i);
			 p(i) = im1;
		 }

		 // Compute elements of [L] for ith row...

		 /* REMINDER: L_{i,i} = 1.0 and L_{i,j} = 0 for all 0 < j < i-1 */

		 c = hess(p(i),i-1)/hess(p(i-1),i-1);
		 hess(p(i),i-1) = c; // L_{i,i-1}

		 // Compute elements of [U] for ith row...

		 for(Index j=i; j<n; ++j) hess(p(i),j) -= c*hess(p(i-1),j);

	 }

}

//! Directly solves [A]{x} = {b} where [A] = [L][U] is (upper) Hessenberg
/*!
 *  Upon input, 'hessLU' is the LU factorization of an (upper) Hessenberg 
 *  coefficient matrix [A], and 'x' is the RHS vector {b}. Upon output, 
 *  'x' is overwritten with the solution vector {x}.
 *
 *  This version employs row pivoting defined by the permutation vector 'p'.
 *
 *  *** THIS IS EXPERIMENTAL - CAVEAT EMPTOR ****
 *
 *  \todo Work out sparisity issues with [L]; when pivoting is used the
 *  structure of [L] is no longer banded.
 */
template<class T>
void solveLU(const HessMatrix<T> & hessLU, const Vector<Index> & p, Vector<T> & x)
{

	 /**** Still under development -- don't use ****/
	 /*  Need to work out sparsity of [L] when pivoting is used */
	 ASSERT( false );

	 // Get problem size...

	 ASSERT( hessLU.size1() == hessLU.size2() );

	 Size n = hessLU.size2();

	 ASSERT( x.size() == n );
	 ASSERT( p.size() == n );

	 // Initialize intermediate vector {d} ...

	 Vector<T> d(n);

	 // Solve [L]{d} = {b} where {b} rhs vector contained in 'x' ...

	 DEBUG_PRINT( "Solving lower system..." );
	 d(0) = x(p(0));
	 for(Index i = 1; i<n; ++i)
		  d(i) = x(p(i)) - hessLU(p(i),i-1)*d(i-1);

	 // Solve [U]{x} = {d} ...
	 DEBUG_PRINT( "Solving upper system..." );
	 T z;
	 Index im1;
	 x(n-1) = d(n-1)/hessLU(p(n-1),n-1);
	 for(Index i=n-1; i > 0; --i)
	 {
		  im1 = i-1;
		  z = 0;
		  for(Index j = i; j < n; ++j) z += hessLU(p(im1),j)*x(j);
		  x(im1) = (d(im1) - z)/hessLU(p(im1),im1);
	 }
}

//! Directly Solves [H]{x} = {b} where [H] is upper Hessenberg
/*!
 *  Solves [H]{x} = {b} using Gauss elimination with row pivoting.
 *
 *  On input, 'hess' is the upper Hessenberg matrix [H] and 'x' is
 *  the RHS vector {b}. On output, 'hess' has been overwritten with
 *  work the pivoted upper triangular matrix [U] and 'x' contains the
 *  solution vector {x}. The returned 'hess' is not particularly useful
 *  to the caller, however, often this function is used as a component
 *  in an algorithm in which preserving [H] is not really needed and
 *  may essentially be destroyed once {x} is known. If preserving [H]
 *  is needed, then one can simply copy [H] to a temporary HessMatrix
 *  prior to calling this routine.
 */
template<class T>
void solveInPlace(HessMatrix<T>& hess, Vector<T>& x)
{

	Size n = x.size();

	ASSERT( hess.size2() == n );

	// Setup pivot array...

	Vector<Index> p(n);	
	for(Index i=0; i<n; ++i)
		p(i) = i;

	// Setup intermediate work vector...

	Vector<T> d(x);

	// Forward pass of Gauss elimination...
	
	for(Index i=1; i<n; ++i)
	{

		// Pivot...

		if( fabs(hess(p(i),i-1)) > fabs(hess(p(i-1),i-1)) )
		{
			Index tmp = p(i-1);
			p(i-1) = p(i);
			p(i) = tmp;
		}

		// Zero element below pivot ...

		Real c = hess(p(i),i-1)/hess(p(i-1),i-1);

		for(Index j=i; j<n; ++j)
			hess(p(i),j) -= c*hess(p(i-1),j);

		d(p(i)) -= c*d(p(i-1));

	}

	// Backward pass...

	for(Index k=n; k>0; --k)
	{
		Index i = k-1;

		Real z(0.0);
		for(Index j=i+1; j<n; ++j)
			z += hess(p(i),j)*x(j);

		ASSERT( !(is_zero(hess(p(i),i))) );

		x(i) = (d(p(i)) - z)/hess(p(i),i);
	}
}

//! Directly solves min J(x), where J(x) = ||{b} - [H]{x}||_2
/*!
 *  On input, 'hess' is the upper Hessinburg matrix [H] and 'x' is the RHS
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
	ASSERT( m = n + 1 );

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
