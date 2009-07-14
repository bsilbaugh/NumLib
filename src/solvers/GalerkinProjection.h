/*! \file GalerkinProjection.h
 */

#ifndef GALERKINPROJECTION_H
#define GALERKINPROJECTION_H

#include "../linalg/Vector.h"
#include "../linalg/HessMatrix.h"
#include "../linalg/HessMatrixExpressions.h"

namespace numlib{ namespace solver{

template<class T>
class GalerkinProjection
{
public:

	 typedef linalg::Vector<T> VecType;
	 typedef linalg::HessMatrix<T> HessType;

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
	  *  performance and require less memeory (only need to store the upper
	  *  triangular matrix instead of both L and U matricies).
	  *
	  *  \todo Allow both 'hess' and 'y' to be sized to mmax instead of m?
	  */
	 T solve(const T & beta, const HessType & extHess, VecType & y)
	  {


		   // Initialize y with RHS...

		   y.zero();
		   y(0) = beta;

		   // Initialize temporary Hessenberg from extended Hessenberg...

		   HessType hess(extHess, false);

		   // Compute LU factorization of hess...

		   linalg::factorLU(hess);

		   // Solve $[H]{y} = \beta e_1$...	

		   linalg::solveLU(hess, y);

		   // Return residual 2-norm of subspace approximation ...

		   Size m = extHess.size2();
		   Index j = m-1;
		   return std::fabs(extHess(j+1,j)*y(j));

	  }

};

}}//::numlib::solver

#endif
