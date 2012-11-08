/*! \file GalerkinProjection.h
 */

#ifndef GALERKINPROJECTION_H
#define GALERKINPROJECTION_H

#include "../linalg/Vector.h"
#include "../linalg/HessMatrix.h"
#include "../linalg/ExtHessMatrix.h"
#include "../linalg/HessMatrixExpressions.h"
#include "../linalg/ExtHessMatrixExpressions.h"

namespace numlib{ namespace solver{

template<class T>
class GalerkinProjection
{
public:

	 typedef linalg::Vector<T> VecType;
	 typedef linalg::ExtHessMatrix<T> HessType;

	 //! Computes the Krylov correction vector per Galerkin projection scheme
	 /*!
	  *  In principle, this projection does not result in the "best" approximation,
	  *  since the error vector is not generally ortho to K. However, in principle
	  *  the cost per iteration of the Galerkin projection is relatively low
	  *  compared to GMRES projection (i.e. solve Hessenburg system as apposed to
	  *  least squares problem).
	  *
	  *  The upper Hessenberg system is solved using a specialized form of Gaussian 
	  *  elimination which takes advantage of the Hessenberg structure. In priciple,
	  *  an specialized form of LU factorization could also be used; however, since
	  *  the factorization would need to be repeated for each subspace expansion,
	  *  it was deemed that Gaussian elimination would provide comparible run-time
	  *  performance.
	  *
	  *  \todo Allow both 'hess' and 'y' to be sized to mmax instead of m?
	  */
	 T solve(const T & beta, const HessType & extHess, VecType & y)
	 {
           typedef numlib::linalg::HessMatrix<T> Hess;

           // Get subspace dimension...
           const Size m = extHess.size2();

           // Check for non-zero subspace, else return...
           if(m == 0) return 0;

		   // Initialize y with RHS...
		   y.zero();
		   y(0) = beta;

		   // Initialize temporary Hessenberg from extended Hessenberg...
		   Hess hess(extHess);

           // Solve system...
		   linalg::solveInPlace(hess, y);

		   // Return residual 2-norm of subspace approximation ...
		   const Index j = m-1;
		   return std::fabs(extHess(j+1,j)*y(j));
	 }

};

}}//::numlib::solver

#endif
