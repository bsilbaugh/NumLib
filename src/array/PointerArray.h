/*! \file PointerArray.h
 *  \brief Contains defintion of PointerArray container
 */
#ifndef POINTERARRAY_H
#define POINTERARRAY_H

#include "../base/numlib-config.h"

namespace numlib{ namespace array{

//! A container for storing an ordered set of base class pointers
/*!
 *	A number of similar containers already exist in the STL and BOOST
 *	libraries. However, the STL containers are designed for dynamic
 *	expansion/reduction of the container; this flexibility comes
 *	at the price of poor iteration performance and/or memory. The 
 *	BOOST library offers a ptr_list, which is similar to the STL list 
 *	with the exception that owernership of the objects ``pointed to'' 
 *	is assumed; thus, delete is called on all pointers stored in the 
 *	container.
 *
 *	For some problems where the size of the required pointer array is
 *	known a-priori (or resize operations occur infrequently), the
 *	data structures and memory management schemes used in the STL 
 *	containers is uneccessary. In addition, some problems arise in
 *	which assuming ownership of the ``pointed to'' objects is not
 *	the desired behavior. This container was designed for such
 *	situations.
 *
 *	Template instantiation follows that of the Boost ptr_list. Thus,
 *	typedef PointerArray<MyObject> MyObjectArray creates an array type
 *	which holds elements of type MyObject*, not MyObject.
 */
template<class T>
class PointerArray
{
public:

	//! Allocates a pointer array large enough to hold n pointers.
	/*!
	 *	If no size argument is provided, the container size defaults to
	 *	0 (empty).
	 */
	PointerArray(Size n_=0);

	//! Copy constructor -- only references duplicated
	PointerArray(const PointerArray & other);

	//! Destructure -- only references deleted
	/*!
	 *	If the objects ``pointed to'' by the pointers in the array
	 *	are to be deleted, use the clear() memeber function to delete
	 *	these objects prior to deleting the PointerArray.
	 */
	~PointerArray();

	//! Assignment operator -- only references duplicated
	PointerArray & operator=(const PointerArray & other);

	//! Returns number of elements in array
	Size size() const;

	//! Resizes array
	/*!
	 *  Performs resize operation on array. Contents of array are
	 *  preserved when size of array is increased. If size of array
	 *  is descreased, elements on the truncated end of the array
	 *  will be lost. Note, only the pointers are deleted when the
	 *  array size is reduced, not the objects ``pointed to''.
	 */
	void resize(Size n_);

	//! Deletes all objects referenced by pointers in the array
	/*!
	 *	This function invokes delete on all pointers contained in the
	 *	array and sets all pointers to NULL.
	 */
	void clear();

	//! Returns a C-style pointer array
	T** c_array() {return data;}

	//! Returns refernce to the ith pointer in the array
	T*&  operator[](Index i);

	//! Returns the ith pointer in the array
	const T* operator[](Index i) const;

private:

	Size n;

	T** data;

	void copy(const PointerArray & other);

	void expand(Size n_);

	void truncate(Size n_);
};

}} //::numlib::array

// Include implimentation file
#include "PointerArray-inl.h"

#endif
