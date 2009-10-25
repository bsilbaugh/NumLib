/*! \File RotInterp.h
 */

#ifndef ROTINTERP_H
#define ROTINTERP_H

#include "../tensor/RotVector.h"
#include "../tensor/FiniteRotations.h"
#include "LinearPW.h"

namespace numlib{ namespace reconstruction{

//! Interpolates a rotation field using LinearPW
/*!
 *  Currently assumes that the total rotation increment over the
 *  entire field is in [0,pi]. Future implementations may rectify
 *  this simplifying assumption.
 */
template<class GridType, class TensorFieldType>
class RotInterp
{
public:

	RotInterp(const GridType& srcGrid, const GridType& dstGrid);

	RotInterp(const RotInterp& other);

	~RotInterp();

	RotInterp& operator=(const RotInterp& other);

	void operator()(const TensorFieldType& srcField, TensorFieldType& dstField);

private:

	typedef numlib::array::Array1D<tensor::RotVector> RotVecField;

	//! Size of source rotation field
	Size nsrc;

	//! Size of destination rotation field
	Size ndst;

	//! Interpolation operator for rotation increments
	LinearPW<GridType, RotVecField> interp;

};

#include "RotInterp-inl.h"

}}//::numlib::reconstruction

#endif
