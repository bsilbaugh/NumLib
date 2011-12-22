/*! \file TensorFieldR1.h */

#ifndef TENSOR_FIELD_R1_H
#define TENSOR_FIELD_R1_H

#include "../base/numlib-config.h"
#include "../base/debug_tools.h"
#include "../base/DivisionByZero.h"

namespace numlib{ namespace tensor{

//! Model of a rank 1 tensor (vector) field in R3
/*!
 *	Element access is via nested classes which implement common container
 *	interfaces; this allows client code to choose the most sensible option
 *	for that particular application.
 */
class TensorFieldR1
{
public:

	TensorFieldR1();

	virtual
	~TensorFieldR1();

	/*------------------------------------------------------------------------*/
	/*                                                     IN-PLACE OPERATORS */

	... FINISH ...

	/*------------------------------------------------------------------------*/
	/*                                                         ELEMENT ACCESS */

	TensorR1& operator()(const Index i);

	const TensorR1& operator()(const Index i) const;

	class Iterator
	{
	public:

		Iterator();

		Iterator(const Iterator& other);

		~Iterator();

		Iterator& operator=(const Iterator& other);

		Iterator& operator==(const Iterator& other);

		TensorR1& operator*();

		TensorR1& operator->();
	};

	Iterator& begin();

	Iterator& end();

};

}}//::numlib::tensor

#endif
