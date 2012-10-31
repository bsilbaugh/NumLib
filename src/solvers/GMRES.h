/*! \file GMRES.h
 */

#ifndef GMRES_H
#define GMRES_H

#include "Krylov.h"
#include "KrylovSpaceAO.h"
#include "GalerkinProjection.h"

//! Generalized Minumum Residual (GMRES) linear solver
/*
 *  \todo Waiting for completion of GMRESProjection
 */
template<class T, class L>
class GMRES: public Krylov<T,L,
						   KrylovSpaceAO<T,L>,
						   GMRESProjection<T> >
{
public:

	GMRES(Size n_, Size mmax_):
		Krylov<T,L,KrylovSpaceAO<T,L>,GMRESProjection<T> >(n_, mmax_)
	{}

private:

	DISALLOW_COPY_AND_ASSIGN( GMRES );

};

#endif
