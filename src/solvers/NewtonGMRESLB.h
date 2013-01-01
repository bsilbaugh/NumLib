/*! \file NewtonGMRESLB.h */

#ifndef NEWTON_GMRES_LB_H
#define NEWTON_GMRES_LB_H

#include "NewtonKrylovLB.h"
#include "KrylovSpaceAO.h"
#include "GMRESProjection.h"

namespace numlib{ namespace solver{

template<class T, class NL>
class NewtonGMRESLB:
	public NewtonKrylovLB<T,NL,KrylovSpaceAO<T,GateauxFD<T,NL> >,GMRESProjection<T> >
{
public:

	NewtonGMRESLB(NL& f_, Size n_, Size mmax_, T alpha_, T beta_, T lambda_min_):
		NewtonKrylovLB<T,NL,KrylovSpaceAO<T,GateauxFD<T,NL> >,GMRESProjection<T> >
		(f_, n_, mmax_, alpha_, beta_, lambda_min_)
		{}

private:
	
	DISALLOW_COPY_AND_ASSIGN( NewtonGMRESLB );

};

}}//::numlib::solver

#endif
