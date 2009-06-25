/*! \file NewtonArnoldi.h
 */

#ifndef NEWTONARNOLDI_H
#define NEWTONARNOLDI_H

#include "NewtonKrylov.h"
#include "KrylovSpaceAO.h"
#include "GalerkinProjection.h"

namespace numlib{ namespace solver{

//! Newton-Arnoldi nonlinear solver
/*!
 *  Specialization of NewtonKrylov nonlinear solver framework which uses
 *  Arnoldi's method (FOM) for the "inner" linear iteration.
 */
template<class T, class NL>
class NewtonArnoldi: public NewtonKrylov<T,
										 NL,
										 KrylovSpaceAO<T,GateauxFD<T,NL> >,
										 GalerkinProjection<T> >
{
public:

	 NewtonArnoldi(Size n_, Size mmax_, Size lmax_, Real tol_);

private:

	 DISALLOW_COPY_AND_ASSIGN( NewtonArnoldi );

};

#include "NewtonArnoldi-inl.h"

}}//::numlib::solver

#endif
