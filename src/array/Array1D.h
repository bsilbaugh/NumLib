/*! \brief Contains Array1D interface
 */

#ifndef ARRAY1D_H
#define ARRAY1D_H

#include <iostream>
#include <iomanip>
#include "ArrayBase.h"
#include "ShapeMismatch.h"

namespace numlib{ namespace array{

//! 1D numerical array interface
template<class T>
class Array1D: private ArrayBase<T>
{
private:

	//! Array size
	Size ni;

public:

	//! Allocates an empty array with number of elements equal to size
	/*!
	 *	Memory for 'size' number of elements is allocated and left
	 *	uninitialized.
	 */
	Array1D(Size imax=0):ArrayBase<T>(imax), ni(imax)
	{
	}

	//! Constructs an array from a raw C pointer to a 1D array
	/*!
	 *	Note that ownership of the data pointed to by data_ is
	 *	assumed. Destruction of the created instance of Array1D will
	 *	result in destruction of the data pointed to by data_.
	 *
	 *	It is assumed that the data is Fortran contiguous; i.e.
	 *	column major.
	 */
	Array1D(T* data_, Size n_):ArrayBase<T>(data_, n_) { }

	//! Copy constructor
	Array1D(const Array1D & arr):ArrayBase<T>(arr) { ni = arr.ni; }

	//! Destructor
	virtual ~Array1D() { }

	//! Assignment from array
	/*!
	 *	Note this this is a deep copy operation; array is
	 *	reallocated to match rhs array. In some array packages,
	 *	array assignment is restricted to arrays of same shape
	 *	and dimension, with the assigment occuring between elements
	 *	of with same index.
	 */
	Array1D & operator=(const Array1D & arr);

	//! Array size
	Size size() const { return ni; }

    //! Resizes array to hold n elements
    void resize(Size imax)
    {
	  ni = imax;
	  ArrayBase<T>::resize(imax);
    }

	//! Read/write element access
	T & operator()(Index i) 
	{ 
		// Check array limits when in debug mode...
		ASSERT( i < ni );

		return ArrayBase<T>::data[i]; 
	}

	//! Const element access
	const T & operator()(Index i) const 
	{ 
		// Check array limits when in debug mode...
		ASSERT( i < ni );

		return ArrayBase<T>::data[i]; 
	}

//	template<class T1>
//	friend std::ostream & operator<<(std::ostream & os, const Array1D<T1> & arr);

	// Add array operators
	
    ARRAY_ALL_OPERATORS(Array1D, T)

};

ARRAY_OVERLOADED_OPERATORS( Array1D )

template<class T>
Array1D<T> & Array1D<T>::operator=(const Array1D<T> & arr)
{
	if(&arr==this)
		return *this;

	ArrayBase<T>::operator=(arr);

	ni = arr.ni;

	return *this;
}

/*
template<class T>
std::ostream & operator<<(std::ostream & os, const Array1D<T> & arr)
{
	for(Index i=0; i<arr.ni; i++)
		os<<" "<<arr.data[i];
	return os;
}
*/

/*
template<>
std::ostream & operator<<(std::ostream & os, const Array1D<double> & arr)
{
	using namespace std;

	for(Index i=0; i<arr.ni; i++)
		os<<setw(16)<<setprecision(8)<<scientific<<arr.data[i];
	return os;
}
*/

} } // numcpp::array
#endif
