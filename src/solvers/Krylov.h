/*! \file Krylov.h
 */

#ifndef KRYLOV_H
#define KRYLOV_H

#include "../linalg/Vector.h"
#include "../linalg/VectorExpressions.h"
#include "../linalg/HessMatrix.h"
#include "../linalg/HessMatrixExpressions.h"

namespace numlib{ namespace solver{

//! Krylov solver framework for linear systems
/*!
 *  The current design only considers Arnoldi/Housholder type orthogonalization.
 *  Support for Lanczos based algorithms, which use a recursive 
 *  biorthogonalization, is best treated in a separate framework. Attempting
 *  to fit both families into the same framework requires significant compromises.
 *  The current emphasis on Arnoldi type algorithms is justified by there 
 *  applicability to non-Hermitian matricies, which arise in many physical models 
 *  of interest. In addition, the Arnoldi and Householder algorithms (which are 
 *  components of this framework) may be used in a separate framework for 
 *  estimating eigenvalues of large sparse matricies.
 *
 *  NOTE: This is code is experimental and subject to revision. Future versions
 *  may not be backwards compatible with old implemenations--caveat emptor.
 *  
 *  \todo Replace use of function prod with an in-place matrix vector product 
 *   to avoid temporaries (e.g. prodIP).
 *
 *  \todo Could also implement this as a template function instead?
 */
template<class T, class L, class K, class P>
class Krylov
{
public:

	 typedef linalg::Vector<T> VecType;
	 typedef linalg::HessMatrix<T> HessType;

	 Krylov(Size n_, Size mmax_);

	 T solve(const L & linO, VecType & x, const VecType & b, const T & tol);

	 Size subSpaceDim() const {return m;}

private:

	 DISALLOW_COPY_AND_ASSIGN( Krylov );

	 Size n;

	 Size m;

	 Size mmax;

	 K krylovSpace;

	 P projectionScheme;

};

#include "Krylov-inl.h"

}}//::numlib::solver

#endif
