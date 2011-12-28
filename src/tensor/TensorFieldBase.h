/*! \file TensorFieldBase.h */

#ifndef TENSOR_FIELD_BASE_H
#define TENSOR_FIELD_BASE_H

#include "../base/ArrayContainer.h"

namespace numlib{ namespace tensor{

//! Generic model of a tensor field
/*!
 *  This class implements data structures, in-place operators, and element
 *  access mechanisms (iterators, dereferencing via [], etc) common to all 
 *  tensor fields. Memory management and element access are inhereted from
 *  ArrayContainer; this class extends ArrayContainer with common inplace
 *  artithmetic operations.
 *
 *  The numlib::ArrayBase and numlib::Array1D classes were not used, as they
 *  define operations that do not make sense for a tensor field; to use one
 *  of the numlib arrays would needlessly complicate compilation, and open the
 *  door to programming errors (via the operators it defines).
 *
 *  The intent is for all tensor fields to subclass from this, and
 *  extend the interface, and define overloaded operators, as needed for 
 *  that particular type of tensor field. Note, we're assuming that each
 *  tensor field implementation will require more than merely specifying
 *  a type parameter; i.e. TensorFieldBase<TensorR1> will not be sufficient
 *  to define a vector field, as a vector field will require additional
 *  member functions to be complete.
 *
 */
template<class T>
class TensorFieldBase: public ArrayContainer<T>
{
public:

	/**************************************************************************
	 *
	 *        Element access interface inhereted from ArrayContainer
	 *
	 *************************************************************************/

protected:

	ArrayContainer<T>::n;

	ArrayContainer<T>::data;

	/*------------------------------------------------------------------------*/
	/*                                                INITIALIZATION AND COPY */

	TensorFieldBase(const Size size):ArrayContainer<T>(size){}

	TensorFieldBase(const TensorFieldBase& other):ArrayContainer<T>(other){}

	virtual
	~TensorFieldBase(){}

	TensorFieldBase& operator=(const TensorFieldBase& other)
	{
		ArrayContainer<T>::operator=(other);
		return *this;
	}

	/*------------------------------------------------------------------------*/
	/*                                                    IN-PLACE ARITHMETIC */

	//! Scalar multiplication
	void multiply_inplace(const Real c)
	{
		for(Index i=0; i<n; ++i)
			data[i] *= c;
	}

	//! Scalar division
	void divide_inplace(const Real c)
	{
		for(Index i=0; i<n; ++i)
			data[i] /= c;
	}

	//! Tensor addition (constant field)
	void constant_add_inplace(const T& u)
	{
		for(Index i=0; i<n; ++i)
			data[i] += u;
	}
	
	//! Tensor subtraction (constant field)
	void constant_subtract_inplace(const T& u)
	{
		for(Index i=0; i<n; ++i)
			data[i] -= u;
	}

	//! Tensor field addition	
	void add_inplace(const TensorFieldBase& other)
	{
		ASSERT( other.size() == n );
		for(Index i=0; i<n; ++i)
			data[i] += other.data[i];
	}

	//! Tensor Field subtraction
	void subtract_inplace(const TensorFieldBase& other)
	{
		ASSERT( other.size() == n );
		for(Index i=0; i<n; ++i)
			data[i] -= other.data[i];
	}

};

}}//::numlib::tensor

//! A macro to implement common inplace arithetic operators
/*!
 *	Macro parameters FTYPE and T correspond to the field
 *	type (subclass name) and element type, respectively.
 *
 *	This macro should be placed in the public field.
 *	It exands to yeild all inplace arithmetic operators
 *	defined by this class, but with the return type
 *	replaced with that of the derived class.
 *
 *	Note that we really can't use inherentance here
 *	(instead of the macros) since the return type would
 *	be that of the base class, not the derived class.
 *	C++ does support covariant return types, however,
 *	this would require the operators to be virtual
 *	and one would still have to explictly override
 *	them with the corrected return type.
 */
#define TENSOR_FIELD_INPLACE_ARITHMETIC( FTYPE, T ) \
	FTYPE& operator*=(const Real c) 				\
	{ 												\
		multiply_inplace(c); 						\
		return *this; 								\
	} 												\
	FTYPE& operator/=(const Real c) 				\
	{ 												\
		divide_inplace(c); 							\
		return *this; 								\
	} 												\
	FTYPE& operator+=(const T& u) 					\
	{ 												\
		constant_add_inplace(u); 					\
		return *this; 								\
	} 												\
	FTYPE& operator-=(const T& u) 					\
	{ 												\
		constant_subtract_inplace(u); 				\
		return *this; 								\
	} 												\
	FTYPE& operator+=(const FTYPE& u) 				\
	{ 												\
		add_inplace(u); 							\
		return *this; 								\
	} 												\
	FTYPE& operator-=(const FTYPE& u) 				\
	{ 												\
		subtract_inplace(u); 						\
		return *this; 								\
	} 

#endif
