/*! \file GMRESProjection
 */

#ifndef GMRESPROJECTION_H
#define GMRESPROJECTION_H

#include "../linalg/Vector.h"
#include "../linalg/ExtHessMatrix.h"
#include "../linalg/ExtHessMatrixExpressions.h"

namespace numlib{ namespace solver{

template<class T>
class GMRESProjection
{
public:

	typedef linalg::Vector<T> VecType;
	typedef linalg::ExtHessMatrix<T> HessType;

	//! Computes the Krylov correction such that residual is A-ortho to K
	/*!
	 *  This projection condition is effected by finding the minimizer, y*, of
	 *  the the residual L2-norm. In principle, this should ensure that the
	 *  error vector is also minimized in L2 (i.e. the error is ortho to K).
	 *
	 *  For use as an "inner" solver of a NewtonKrylov scheme, Brown and Saad
	 *  (1990) showed that the GMRES projection gives better "descent directions"
	 *  than Arnoldi's method (Galerkin projection scheme). So, in practice,
	 *  the expectation is that GMRES will generally be favored over the Galerkin
	 *  projection scheme.
	 */
	T solve(const T & beta, const HessType & hess, VecType & y)
	{
		// Initialize RHS...
		VecType g(y.size() + 1);
		g.zero();
		g(0) = beta;

		// Solve least square problem ...
		HessType h(hess);
		linalg::solveInPlaceLeastSquare(h, g); /* g over-written with soln and res norm*/

		// Extract soln vector and residual norm...
		const Size n = y.size();
		for(Index i=0; i<n; ++i)
			y(i) = g(i);
		const Real rn = std::fabs(g(n));

		// Return residual norm of subspace approximation...
		return rn;
	}

};

}}//::numlib::solver

#endif
