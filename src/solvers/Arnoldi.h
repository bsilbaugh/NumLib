/*! \file Arnoldi.h
 */

#ifndef ARNOLDI_H
#define ARNOLDI_H

#include "Krylov.h"
#include "KrylovSpaceAO.h"
#include "GalerkinProjection.h"

namespace numlib{ namespace solver{

template<class T, class L>
class Arnoldi: public Krylov<T,L,
							 KrylovSpaceAO<T,L>,
							 GalerkinProjection<T> >
{
public:

	 Arnoldi(Size n_, Size mmax_):
		  Krylov<T,L,
				 KrylovSpaceAO<T,L>,
				 GalerkinProjection<T> >(n_, mmax_)
     {}

private:

	 DISALLOW_COPY_AND_ASSIGN( Arnoldi );
};

}}//::numlib::solver

#endif
