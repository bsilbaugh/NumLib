/*! \file TensorFieldR0.h */

#ifndef TENSOR_FIELD_R0_H
#define TENSOR_FIELD_R0_H

#include "TensorFieldBase.h"

namespace numlib{ namespace tensor{

//! Model of a rank-0 tensor field (a scalar field)
class TensorFieldR0:
	public TensorFieldBase<Real>
{
public:

	TensorFieldR0(const Size size=0):TensorFieldBase<Real>(size){}

	TensorFieldR0(const TensorFieldR0& other):TensorFieldBase<Real>(other){}

	virtual
	~TensorFieldR0(){}

	TensorFieldR0& operator=(const TensorFieldR0& other)
	{
		TensorFieldBase<Real>::operator=(other);
		return *this;
	}

	/**************************************************************************
	 *     ELEMENT ACCESS INTERFACE INHERITED FROM TensorField BASE CLASS      
	 **************************************************************************/

	/*------------------------------------------------------------------------*/
	/*                                                    IN-PLACE ARITHMETIC */

	TENSOR_FIELD_INPLACE_ARITHMETIC( TensorFieldR0, Real );

};

/*----------------------------------------------------------------------------*/
/*                                                         OPERATOR OVERLOADS */

TENSOR_FIELD_ARITHMETIC_OVERLOADS( TensorFieldR0, Real );

}}//::numlib::tensor

#endif
