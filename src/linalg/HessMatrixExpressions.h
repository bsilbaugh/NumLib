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

//! Computes the LU factorization of [A]
/*!
 *  LU factorization is performed in place to minimize memory requirements
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

}}//::numlib::linalg

#endif
