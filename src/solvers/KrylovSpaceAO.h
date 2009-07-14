/*! \file KrylovSpaceAO
 */

#ifndef KRYLOVSPACEAO_H
#define KRYLOVSPACEAO_H

#include "../base/debug_tools.h"
#include "../base/nocopy.h"
#include "../base/numlib-config.h"
#include "../linalg/Vector.h"
#include "../linalg/HessMatrix.h"

namespace numlib{ namespace solver{

//! Implements Arnoldi Orthogonalization algorithm
/*!
 *  The Arnoldi Orthogonolization algorithm is one of the least complex algorithms
 *  for constructing a Krylov basis. However, if numerical conditioning becomes
 *  an issue, consider switching to Householder orthogonolization; this is a
 *  more complex algorithm, but it has been shown to be quite robust.
 *
 *  Template parameters:
 *  - T := Numerical type (e.g. Real, Complex)
 *  - L := Linear operator type (e.g. Matrix, SparseMatrix, etc), see note 1.
 *
 *  NOTES:
 *  1. Linear operator type is any type that maps a vector to another vector via
 *     the matrix-vector product function, v = prod(A, u), where A is an intance
 *     of the linear operator. The operator A need not be a matrix type. Examples
 *     of non-matrix type examples of A include Fast-Multipole expansions, and 
 *     directional derivatives of a nonlinear operator.
 */
template<class T, class L>
class KrylovSpaceAO
{
public:

	 typedef linalg::Vector<T> VecType;
	 typedef linalg::HessMatrix<T> HessType;

	 //! Constructs a Krylov space with maximum dimension of maxSpaceDim
	 /*!
	  *  The dimension of the space in which the Krylov space is embeded is
	  *  specified by 'n'.
	  *
	  *  The initial dimension of the Krylov space is 0.
	  */
	 KrylovSpaceAO(Size n_, Size maxSpaceDim);

	 //! Returns the current space dimension
	 Size size(){return m;}

	 //! Constructs a Krylov space up to maximum specified space dimension
	 /*!
	  *  This is effectively a wrapper around member functions 'seed' and
	  *  'expandSpace'. During the process of constructing the Krylov space,
	  *  the norm of the j+1 Krylov basis vector, Av, is monitored. When the
	  *  norm of this vector drops below the specified threshold, tol, a
	  *  "happy" breakdown is declared and the construction of the space is
	  *  terminated early with m < mmax.
	  */
	 void buildSpace(const L & linO, const VecType & r, const T & tol);

	 //! Sets the Hessenberg matrix representation of the projection of A onto K
	 /*!
	  *  The projection of A onto K is computed as a byproduct of the subspace
	  *  expansion. Thus, this function may be used to simply "fetch" the result
	  *  if/when it is required. Here, A is the linear operator 'linO' provided
	  *  to 'expandSpace' member function.
	  *
	  *  The result is returned in the form of an "extended" Hessenberg matrix,
	  *  which has dimension m+1 x m.
	  *
	  *  \todo Is there a clean way to avoid copy operation?
	  */
	 void projA(HessType & h);

	 //! Maps the vector y in K to vector z in R^n
	 void map(const VecType & y, VecType & z);

private:

	 DISALLOW_COPY_AND_ASSIGN( KrylovSpaceAO );

	 //! Superspace dimension
	 Size n;

	 //! Current space dimension
	 Size m;

	 //! Maximum space dimension
	 Size mmax;

	 //! Orthonormal basis vector set
	 VecType* basis;

	 //! Matrix representation of A in K
	 HessType hess;

};

#include "KrylovSpaceAO-inl.h"

}}//::numlib::solver

#endif
