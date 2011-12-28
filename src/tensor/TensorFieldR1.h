/*! \file TensorFieldR1.h */

#ifndef TENSOR_FIELD_R1_H
#define TENSOR_FIELD_R1_H

#include "TensorFieldBase.h"
#include "TensorExpressions.h"

namespace numlib{ namespace tensor{

//! Model of a rank-1 tensor field (a vector field)
class TensorFieldR1:
	public TensorFieldBase<TensorR1>
{
public:

	TensorFieldR1(const Size size=0):TensorFieldBase<TensorR1>(size){}

	TensorFieldR1(const TensorFieldR1& other):TensorFieldBase<TensorR1>(other){}

	virtual
	~TensorFieldR1(){}

	TensorFieldR1& operator=(const TensorFieldR1& other)
	{
		TensorFieldBase<TensorR1>::operator=(other);
		return *this;
	}

	/**************************************************************************
	 *     ELEMENT ACCESS INTERFACE INHERITED FROM TensorField BASE CLASS      
	 **************************************************************************/

	/*------------------------------------------------------------------------*/
	/*                                                    IN-PLACE ARITHMETIC */

	TENSOR_FIELD_INPLACE_ARITHMETIC( TensorFieldR1, TensorR1 );

	//! (left) dot product
	/*!
	 *  Equivolent to u = u * a, where * denotes the dot (inner) product
	 *  of the rank1 tensor u with the rank 2 tensor a.
	 *
	 *  \todo Add inplace dot product with TensorR1 to TensorR1 and
	 *  reimplement this function.
	 */
	TensorFieldR1& operator*=(const TensorR2& a)
	{
		ASSERT( data );
		for(Index i=0; i<n; ++i)
			data[i] = dot(data[i], a);
	}
};

}}//::numlib::tensor

#endif
