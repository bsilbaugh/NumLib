/*! \brief Array2D interface
 */

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <iostream>
#include <iomanip>
#include "ArrayBase.h"

namespace numlib{ namespace array{

//! 2D numerical array
/*!
 *	Extends ArrayBase with 2D array interface. Elements are stored as
 *	column major (e.g. Fortran). Column major storage was chosen to 
 *	facilitate interoperability with Fortran libraries. Matlab also uses
 *	column major storage, hence interoperability with Matlab (via mex)
 *	should be possible.
 */
template<class T>
class Array2D: private ArrayBase<T>
{
private:

	//! Array dimensions
	Size ni, nj;

	//! Array strides
	/*!
	 *  si := stride corresponding to first axis
	 *  sj := strid corresponding to second axis
	 *
	 *  Despite the column major storage, si is allowed to be non-unity
	 *  This allowed for efficient in-place transposition of array contents.
	 */
	Size si, sj;

public:

	//! Allocates an emtpy array with imax*jmax elements
	/*!
	 * 	Memory for imax*jmax number of elements is allocated
	 * 	and left uninitialized.
	 */
	Array2D(Size imax_=0, Size jmax_=0):ArrayBase<T>(imax_*jmax_),
	ni(imax_), nj(jmax_), si(1),sj(imax_){ }

	//! Copy constructor
	Array2D(const Array2D & arr):ArrayBase<T>(arr), 
	ni(arr.ni), nj(arr.nj), si(arr.si), sj(arr.sj){ }

	//! Assignment from array
	/*!
	 *	See Array1D for additional details -- implements similar
	 *	assignment/copy protocals.
	 */
	Array2D & operator=(const Array2D & arr);

	//! Array size - number of elements along first axis
	/*!	
	 *  Depreciated 
	 */
	Size imax() const { return ni; }

	//! Array size - number of elements along first axis
	Size size1() const {return ni;}

	//! Array size - number of elements along second axis
	/*!	
	 *  Depreciated 
	 */
	Size jmax() const {return nj; }

	//! Array size - number of elements along second axis
	Size size2() const {return nj; }

    //! Resizes array to hold imax rows and jmax columns
    /*!
	 *  Original contents of the array are not guaranteed to be preserved.
	 *  The resize operation is intended for initialization of default constructed
	 *  arrays.
	 */
    void resize(Size imax_, Size jmax_)
    {
	    ni = imax_;
	    nj = jmax_;
		sj = imax_;
	    ArrayBase<T>::resize(ni*nj);
	}


	//! Read/write element access
	T & operator()(Index i, Index j) 
	{ 
		ASSERT( (i < ni) );
		ASSERT( (j < nj) );
		return ArrayBase<T>::data[i*si + j*sj]; 
	}

	//! Const element access
	const T & operator()(Index i, Index j) const 
	{ 
		ASSERT( (i < ni) );
		ASSERT( (j < nj) );
		return ArrayBase<T>::data[i*si + j*sj]; 
	}

	template<class T1>
	friend std::ostream & operator<<(std::ostream & os, const Array2D<T1> & arr);

	// Add array operators
	
	ARRAY_ALL_OPERATORS(Array2D, T)
};

ARRAY_OVERLOADED_OPERATORS(Array2D)

template<class T>
Array2D<T> & Array2D<T>::operator=(const Array2D<T> & arr)
{
	if(&arr==this)
		return *this;

	ArrayBase<T>::operator=(arr);

	ni = arr.ni;
	nj = arr.nj;
	si = arr.si;
	sj = arr.sj;

	return *this;
}


template<class T>
std::ostream & operator<<(std::ostream & os, const Array2D<T> & arr)
{
	using namespace std;

	Index i, j;

	for(i=0; i<arr.ni; i++)
	{
		for(j=0; j<arr.nj; j++)
			os<<" "<<arr(i,j);
		os<<endl;
	}
	return os;
}

/*
template<>
std::ostream & operator<<(std::ostream & os, const Array2D<double> & arr)
{
	using namespace std;

	Index i, j;

	for(i=0; i<arr.ni; i++)
	{
		for(j=0; j<arr.nj; j++)
			os<<setw(16)<<setprecision(8)<<scientific<<arr(i,j);
		os<<endl;
	}
	return os;
}
*/

}} //numlib::array

#endif
