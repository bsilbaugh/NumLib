/*! \file TriMatrixExpressions.h
 */

#include "../array/Array1D.h"
#include "Vector.h"
#include "TriMatrix.h"

namespace numlib{ namespace linalg{

//! Evaluates the left tri-diagonal matrix vector product
template<class T>
Vector<T> prod(const TriMatrix<T> & a, const Vector<T> & u)
{
  ASSERT(u.size() == a.size1());
  Size n = u.size();
  T zero(0);
  Vector<T> v(n);

  for(Index i=0; i<n; ++i)
	v(i) = a.diagBand(i)*u(i);

  for(Index i=0; i<n-1; ++i)
  {
	v(i+1) += a.lowerBand(i+1)*u(i);
	v(i) += a.upperBand(i)*u(i+1);
  }

  return v;

}

//! Solves the tri-diagonal system B({a},{b},{c}){x} = {b}
/*!
 *  The tri-diagonal system is solved using the Thomas algorithm. The
 *  Thomas algorithm is effectively a specialization of Gaussian elimination
 *  which leverages the banded matrix structure to reduce the algorithmic
 *  complexity from O(n^3) to O(n).
 *
 *  The current implementation does not employ row pivoting. Row pivoting
 *  is not needed provided that the matrix is diagonally dominant. In most
 *  practical cases involving tri-diagonal matricies, diagonal dominance is
 *  expected; e.g. discrete solutions to the 1D Poisson's equation and
 *  cubic spline interpolation.
 *
 *  Upon input, 'rhs' is assumed to be initialized with the RHS vector {b}.
 *  Upon output, 'rhs' contains the solution vector {x}.
 */ 
template<class T>
void solveThomas(const TriMatrix<T> & a, Vector<T> & rhs)
{

	 ASSERT( a.size1() == rhs.size() );

	 // Get problem size...

	 Size n = rhs.size();

	 DEBUG_PRINT_VAR( n );

	 // Create temporary work array to store intermediate upper band...

	 array::Array1D<T> u(n);

	 /* Forward Pass */

	 DEBUG_PRINT( "Executing forward pass." );

	 T c;
	 T d;

	 d = a.diag(0);
	 u(0) = a.upper(0)/d;
     rhs(0) /= d;
	 for(Index i=1; i<n; ++i)
	 {
		  c = a.lower(i);
		  d = a.diag(i) - c*u(i-1);
		  u(i) = a.upper(i)/d;
		  rhs(i) = (rhs(i) - c*rhs(i-1))/d;
  	 }

	 /* Backward Pass */

	 DEBUG_PRINT( "Executing backward pass." );
	 
	 for(Index i=n-1; i>0; --i)
		  rhs(i-1) = rhs(i-1) - u(i-1)*rhs(i);
}

}}//::numlib::linalg
