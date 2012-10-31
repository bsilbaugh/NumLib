/*! \file NewtonGMRES.h */

#ifndef NEWTON_GMRES
#define NEWTON_GMRES

#include "NewtonKrylov.h"
#include "KrylovSpaceAO.h"
#include "GMRESProjection.h"

namespace numlib{ namespace solver{

//! Newton-GMRES nonlinear solver
/*!
 *	Specialization of NewtonKrylov nonlinear solver framework which uses
 *	GMRES for the "inner" linear iteration.
 */
template<class T, class NL>
class NewtonGMRES:
	public NewtonKrylov<T,NL,
					    KrylovSpaceAO<T,GateauxFD<T,NL> >,
						GMRESProjection<T> >
{
public:

	NewtonGMRES(Size n_, Size mmax_, Size lmax_, Real tol_):
		NewtonKrylov<T,NL,
			KrylovSpaceAO<T,GateauxFD<T,NL> >,
			GMRESProjection<T> >(n_, mmax_, lmax_, tol_)
	{}

private:

	DISALLOW_COPY_AND_ASSIGN( NewtonGMRES );

};

}}//::numlib::solver

#endif
