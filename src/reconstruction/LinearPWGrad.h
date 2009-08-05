/*! \file LinearPWGrad.h
 */

#ifndef LINEARPWGRAD_H
#define LINEARPWGRAD_H

#include "../array/Array1D.h"
#include "interp_utils.h"

namespace numlib{ namespace reconstruction{

//! Reconstruction operator for a vector function on a 1D domain
/*!
 *  Reconstruction of function gradient is based on piece-wise linear
 *  interpolation basis functions.
 *
 *  Template parameters:
 *  T := Any scalar numeric type
 *  GridType := Any 1D array like container
 *  VecFieldType := Any 1D array like container containing vector numeric types
 */
template<class GridType, class VecFieldType>
class LinearPWGrad
{
public:

	 LinearPWGrad(const GridType & srcGrid, const GridType & dstGrid);

	 LinearPWGrad(const LinearPWGrad & other);

	 ~LinearPWGrad();

	 LinearPWGrad & operator=(const LinearPWGrad & other);

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

	 //! Partition array
	 array::Array1D<Index> p;

	 //! Copy helper function
	 void copy(const LinearPWGrad & other);

};

#include "LinearPWGrad-inl.h"

}}//::numlib::reconstruction

#endif
