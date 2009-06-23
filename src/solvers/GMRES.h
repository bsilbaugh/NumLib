/*! \file GMRES.h
 */

#ifndef GMRES_H
#define GMRES_H

//! Generalized Minumum Residual (GMRES) linear solver
/*
 *  \todo Waiting for completion of GMRESProjection
 */
template<class T, class L>
class GMRES: public Krylov<T,L,KrylovSpaceAO,GMRESProjection>
{
	 **** FINISH ME *****
};

#endif
