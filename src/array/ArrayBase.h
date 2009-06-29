/*! \brief Contains ArrayBase
 */

#ifndef ARRAYBASE_H
#define ARRAYBASE_H

#include <iostream>
#include <iomanip>

#include "../base/debug_tools.h"
#include "../base/numlib-config.h"
#include "ShapeMismatch.h"

namespace numlib{ namespace array{


//! Numerical array base class
/*!
 *	Defines the underlying data structure and array operators
 *	used by numerical array subclasses. Centralizing the implementation
 *	of array operators was done to simplify code maintenance and 
 *	facilitate conditional complilation of future implementation
 *	options (e.g. debugging checks such as index exceeding arrays bounds,
 *	etc).
 *
 *	Public interface to array elements is expected to be provided
 *	by subclasses; in priniciple subclasses need only define the
 *	appropriate interface for mapping array indicies to memory.
 *
 *	In future, may want to delegate array operations to fortran lib
 *	for compatible element data types?
 */
template<class T>
class ArrayBase
{
protected:

	//! Array size (number of elements)
	Size n;

	//! Array data pointer
	T* data;

public:

	//! Allocates an empty array with number of elements equal to size
	/*!
	 *	Memory for 'size' number of elements is allocated and left
	 *	uninitialized.
	 */
	ArrayBase(Size size=0);

	//! Constructs an array from a raw C pointer to a 1D array
	/*!
	 *	Note that ownership of the data pointed to by data_ is
	 *	assumed. Destruction of the created instance of ArrayBase will
	 *	result in destruction of the data pointed to by data_.
	 *
	 *	It is assumed that the data is Fortran contiguous; i.e.
	 *	column major.
	 */
	ArrayBase(T* data_, Size size):data(data_), n(size)
	{
	}

	//! Copy constructor
	ArrayBase(const ArrayBase & arr);

	//! Destructor
	virtual ~ArrayBase();

	//! Returns total number of elements contained in the array
	Size size(){return n;}

    //! Reallocates internal memory to hold n elements
    /*! 
     *  Original data is not guaranteed to be preserved. The resize operation
     *  is provided primarily for initialization of default constructed arrays.
     */
    void resize(Size n_);

	//! Assignment from array
	/*!
	 *	Note this this is a deep copy operation; array is
	 *	reallocated to match rhs array. In some array packages,
	 *	array assignment is restricted to arrays of same shape
	 *	and dimension, with the assigment occuring between elements
	 *	of with same index.
	 */
	ArrayBase & operator=(const ArrayBase & arr);

	//! Assignment from scalar
	/*!
	 *	All elements of the array are assigned the value given
	 *	of the input object 'x'. For example, to initialize an
	 *	array of type double with N elements to zero, the following
	 *	could be used:
	 *
	 *		ArrayBase<double> arr(N);
	 *		arr = 0.0;
	 *
	 */
	void operator=(const T & x);

	// *** IN-PLACE ARRAY OPERATORS ***

	//! In-place scalar addition
	void operator+=(const T & x);

	//! In-place scalar subtraction
	void operator-=(const T & x);

	//! In-place scalar multiplication
	void operator*=(const T & x);

	//! In-place scalar division
	void operator/=(const T & x);

	//! In-place array addition
	void operator+=(const ArrayBase & arr);

	//! In-place array subtraction
	void operator-=(const ArrayBase & arr);

	//! In-place array multiplication
	void operator*=(const ArrayBase & arr);

	//! In-place array division
	void operator/=(const ArrayBase & arr);

};

/* IMPLEMENTATION DETAILS */

template<class T>
ArrayBase<T>::ArrayBase(Size size)
{
	n = size;
	data = new T[n];
}

template<class T>
ArrayBase<T>::ArrayBase(const ArrayBase & arr)
{
	n = arr.n;
	data = new T[n];
	for (Index i=0; i<n; i++)
		data[i] = arr.data[i];
}

template<class T>
ArrayBase<T>::~ArrayBase()
{
	delete [] data;
	n = 0;
}

template<class T>
ArrayBase<T> &  ArrayBase<T>::operator=(const ArrayBase & arr)
{
	if(&arr==this)
		return *this;

	delete[] data;

	n = arr.n;
	data = new T[n];
	for(Index i=0; i<n; i++)
		data[i] = arr.data[i];

	return *this;
}

template<class T>
void ArrayBase<T>::resize(Size size)
{
  n = size;
  delete[] data;
  data = new T[n];
}

template<class T>
void ArrayBase<T>::operator=(const T & x)
{
	for(Index i=0; i<n; i++)
		data[i] = x;
}

template<class T>
void ArrayBase<T>::operator+=(const T & x)
{
	for(Index i=0; i<n; i++)
		data[i] += x;
}

template<class T>
void ArrayBase<T>::operator-=(const T & x)
{
	for(Index i=0; i<n; i++)
		data[i] -= x;
}

template<class T>
void ArrayBase<T>::operator*=(const T & x)
{
	for(Index i=0; i<n; i++)
		data[i] *= x;
}

template<class T>
void ArrayBase<T>::operator/=(const T & x)
{
	for(Index i=0; i<n; i++)
		data[i] /= x;
}

template<class T>
void ArrayBase<T>::operator+=(const ArrayBase<T> & arr)
{

	if(n != arr.n) throw ShapeMismatch();

	for(Index i=0; i<n; i++)
		data[i] += arr.data[i];
}

template<class T>
void ArrayBase<T>::operator-=(const ArrayBase<T> & arr)
{
	if(n != arr.n) throw ShapeMismatch();

	for(Index i=0; i<n; i++)
		data[i] -= arr.data[i];
}

template<class T>
void ArrayBase<T>::operator*=(const ArrayBase<T> & arr)
{
	if(n != arr.n) throw ShapeMismatch();

	for(Index i=0; i<n; i++)
		data[i] *= arr.data[i];
}

template<class T>
void ArrayBase<T>::operator/=(const ArrayBase<T> & arr)
{

	if(n != arr.n) throw ShapeMismatch();

	for(Index i=0; i<n; i++)
		data[i] /= arr.data[i];
}

} } //numcpp::array


// A useful macro to work around lack of covariant return types with
// C++ template classes. If you use public inherentance to expose
// these methods in your derived class, the return type will be ArrayBase
// and not that of your derived class. If this were a proper C++ class
// (not a template) one could declare each operator as virtual and then
// overwrite the return type with the proper derived class; however, this
// use of ``covariant'' return types does not appear to be supported for
// template classes (based on gcc 4.0). So, to avoid the re-writting 
// the plethora of arithetic operators for your derived class, you may
// use this macro to add the respective inline operators to your class 
// with the proper return type.
//
// There may be a very elegant way of acheiving this using advanced template
// metaprograming techniques. Considering current time constraints, however,
// this will have to suffice.

#define ARRAY_INPLACE_OPERATORS(Tsub, T)			\
													\
	Tsub & operator=(const T & x) 					\
	{ 												\
		ArrayBase<T>::operator=(x); 				\
		return *this; 								\
 	}												\
													\
	Tsub & operator+=(const T & x) 					\
	{ 												\
		ArrayBase<T>::operator+=(x); 				\
		return *this; 								\
 	}												\
													\
	Tsub & operator-=(const T & x) 					\
	{ 												\
		ArrayBase<T>::operator-=(x); 				\
		return *this; 								\
 	}												\
													\
	Tsub & operator*=(const T & x) 					\
	{ 												\
		ArrayBase<T>::operator*=(x); 				\
		return *this; 								\
 	}												\
													\
	Tsub & operator/=(const T & x) 					\
	{ 												\
		ArrayBase<T>::operator/=(x); 				\
		return *this; 								\
 	}												\
													\
	Tsub & operator+=(const Tsub & arr)				\
	{ 												\
		ArrayBase<T>::operator+=(arr); 				\
		return *this; 								\
 	}												\
													\
	Tsub & operator-=(const Tsub & arr)				\
	{ 												\
		ArrayBase<T>::operator-=(arr); 				\
		return *this; 								\
 	}												\
													\
	Tsub & operator*=(const Tsub & arr)				\
	{ 												\
		ArrayBase<T>::operator*=(arr); 				\
		return *this; 								\
 	}												\
													\
	Tsub & operator/=(const Tsub & arr)				\
	{ 												\
		ArrayBase<T>::operator/=(arr); 				\
		return *this; 								\
 	}												\

#define ARRAY_CONST_OPERATORS(Tsub, T) 				\
													\
	Tsub operator+(const T & x) const				\
	{ 												\
		Tsub tmp(*this);							\
		tmp += x;									\
		return tmp;									\
	}												\
													\
	Tsub operator-(const T & x) const				\
	{ 												\
		Tsub tmp(*this);							\
		tmp -= x;									\
		return tmp;									\
	} 												\
													\
	Tsub operator*(const T & x) const				\
	{ 												\
		Tsub tmp(*this);							\
		tmp *= x;									\
		return tmp;									\
	} 												\
													\
	Tsub operator/(const T & x) const				\
	{ 												\
		Tsub tmp(*this);							\
		tmp /= x;									\
		return tmp;									\
	} 												\
													\
	Tsub operator+(const Tsub & x) const			\
	{ 												\
		Tsub tmp(*this);							\
		tmp += x;									\
		return tmp;									\
	}												\
													\
	Tsub operator-(const Tsub & x) const			\
	{ 												\
		Tsub tmp(*this);							\
		tmp -= x;									\
		return tmp;									\
	} 												\
													\
	Tsub operator*(const Tsub & x) const			\
	{ 												\
		Tsub tmp(*this);							\
		tmp *= x;									\
		return tmp;									\
	} 												\
													\
	Tsub operator/(const Tsub & x) const			\
	{ 												\
		Tsub tmp(*this);							\
		tmp /= x;									\
		return tmp;									\
	} 												\


#define ARRAY_FRIEND_OPERATORS(Tsub, TT)

#define ARRAY_OVERLOADED_OPERATORS(Tsub)			        \
	 														\
	 template<class TT>										\
	 Tsub<TT> operator+(const TT & x, const Tsub<TT> & arr)	\
	 {														\
		  return arr + x;									\
	 }														\
	 														\
     template<class TT>										\
	 Tsub<TT> operator-(const TT & x, const Tsub<TT> & arr)	\
	 {														\
		  return -1.0*(arr - x);							\
	 }														\
	 														\
	 template<class TT>										\
	 Tsub<TT> operator*(const TT & x, const Tsub<TT> & arr)	\
	 {														\
		  return arr * x;									\
	 }														\
	 														\
	 template<class TT>										\
	 Tsub<TT> operator/(const TT & x, const Tsub<TT> & arr)	\
	 {														\
		  Tsub<TT> tmp(arr.n);								\
		  for(Index i=0; i<arr.size(); i++)					\
			   tmp(i) = x/arr(i);							\
		  return tmp;										\
	 }														\
	 														\
	 template<class TT>										\
	 Tsub<TT> abs(const Tsub<TT> & arr)						\
	 {														\
		  Tsub<TT> tmp(arr.n);								\
		  for(Index i=0; i<arr.size(); i++)					\
			   tmp(i) = ::numlib::abs(arr(i));				\
		  return tmp;										\
	 }														\
	 														\
	 template<class TT>										\
	 TT sum(const Tsub<TT> & arr)							\
	 {														\
		  TT tmp = 0;										\
		  for(Index i=0; i<arr.size(); ++i)					\
			   tmp += arr(i);								\
		  return tmp;										\
	 }														\

#define ARRAY_ALL_OPERATORS(Tsub, T) 		\
		ARRAY_INPLACE_OPERATORS(Tsub, T) 	\
		ARRAY_CONST_OPERATORS(Tsub, T) 		\
		ARRAY_FRIEND_OPERATORS(Tsub,T)

#endif
