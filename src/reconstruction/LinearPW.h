/*! \file LinearPW.h
 */

#ifndef LINEARPW_H
#define LINEARPW_H

#include "../array/Array1D.h"
#include "interp_utils.h"

namespace numlib{ namespace reconstruction{

//! Piece-wise linear interpolation operator
/*!
 *  Peforms piece-wise linear interpolation between pre-defined source
 *  and destination grids. Interpolation basis functions and pre-computed
 *  and stored for reuse. Linear extrapolation is performed for unbounded
 *  points.
 *
 *  Template parameters:
 *  GridType := Any 1D array like container
 *  VecFieldType := Any 1D array like container containing vector numeric types
 */
template<class GridType, class VecFieldType>
class LinearPW
{
public:

	 LinearPW(const GridType & srcGrid, const GridType & dstGrid);

	 LinearPW(const LinearPW & other);

	 ~LinearPW();

	 LinearPW & operator=(const LinearPW & other);

	 void operator()(const VecFieldType & srcField, VecFieldType & dstField);
  
private:

	 //! Number of source points
	 Size nsrc;

	 //! Number of destination (target) points
	 Size ndst;

	 //! Left linear basis function
	 array::Array1D<Real> basisL;

	 //! Right linear basis function
	 array::Array1D<Real> basisR;

	 //! Interpolation intervals
	 array::Array1D<Index> p;

	 //! Copy helper function
	 void copy(const LinearPW & other);

};

#include "LinearPW-inl.h"

}}//::numlib::reconstruction

#endif
