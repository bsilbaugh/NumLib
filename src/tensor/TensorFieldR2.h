/*! \file TensorFieldR2.h */

#ifndef TENSOR_FIELD_R2_H
#define TENSOR_FIELD_R2_H

#include "TensorFieldBase.h"
#include "TensorExpressions.h"

namespace numlib{ namespace tensor{

//! Model of a rank-2 tensor field
class TensorFieldR2:
	public TensorFieldBase<TensorR2>
{
public:

	TensorFieldR2(const Size size=0):TensorFieldBase<TensorR2>(size){}

	TensorFieldR2(const TensorFieldR2& other):TensorFieldBase<TensorR2>(other){}

	virtual
	~TensorFieldR2(){}

	TensorFieldR2& operator=(const TensorFieldR2& other)
	{
		TensorFieldBase<TensorR2>::operator=(other);
		return *this;
	}

	/**************************************************************************
	 *     ELEMENT ACCESS INTERFACE INHERITED FROM TensorField BASE CLASS      
	 **************************************************************************/

	/*------------------------------------------------------------------------*/
	/*                                                    IN-PLACE ARITHMETIC */

	TENSOR_FIELD_INPLACE_ARITHMETIC( TensorFieldR2, TensorR2 );

};

/*----------------------------------------------------------------------------*/
/*                                                         OPERATOR OVERLOADS */

TENSOR_FIELD_ARITHMETIC_OVERLOADS( TensorFieldR2, TensorR2 );

}}//::numlib::tensor

#endif
