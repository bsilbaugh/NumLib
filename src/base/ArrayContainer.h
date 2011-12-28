/*! \file ArrayContainer */

#ifndef ARRAY_CONTAINER_H
#define ARRAY_CONTAINER_H

#include "numlib-config.h"
#include "debug_tools.h"

namespace numlib{

//! A simple, generic, implementation of a resizable array
/*!
 *	This implements a very simple array container with the usual
 *	element access operators and iterators. This container is
 *	a compliment to the standard STL containers in that it 
 *	assumes the array size remains fixed once initialized. This
 *	assumption allows this container to be very lightweight
 *	and implement fast iterators and element lookup.
 *
 *	If you need dynamic resizing (e.g. element insertion, deletion, etc)
 *	then you should use one of the STL containers. STL containers are
 *	very well designed, and some compilers can better optimize STL containers
 *	since they can safely make assumptions regarding their usage.
 *
 *	This class does not provide any arithmetic operators or related member
 *	functions. The purpose of this class is limited to memory management and
 *	element access. However, this class may be used as a foundation for
 *	defining numerical arrays and other field types.
 *
 */
template<class T>
class ArrayContainer
{
public:

	typedef T ValueType;

	/*------------------------------------------------------------------------*/
	/*                                         INITIALIZATION AND DUPLICATION */

	//! Initializes an array for n elements (default 0)
	ArrayContainer(const Size size=0):
		n(size),
		data(NULL)
	{
		data = new T[n];
	}

	//! Deep copy initialization
	ArrayContainer(const ArrayContainer& other):data(NULL)
	{
		ASSERT( other.data );
		n = other.n;
		data = new T[n];
		for(Index i=0; i<n; ++i)
			data[i] = other.data[i];
	}

	virtual
	~ArrayContainer()
	{
		delete[] data;
	}

	//! Deep copy assignment
	ArrayContainer& operator=(const ArrayContainer& other)
	{
		if(&other==this) return *this;
		// Free old data...
		n = other.n;
		delete[] data;
		// Allocate memory for new data...
		n = other.n;
		data = new T[n];
		// Copy data over from other...
		for(Index i=0; i<n; ++i)
			data[i] = other.data[i];
		// Return reference to this object...
		return *this;
	}

	/*------------------------------------------------------------------------*/
	/*                                                         ELEMENT ACCESS */

	//! Returns number of elements in the array
	const Size size() const {return n;}

	//! Resizes the array to hold n elements
	/*!
	 *	This does not preserve contents!
	 */
	void resize(const Size size)
	{
		delete[] data;
		n = size;
		data = new T[n];
	}

	//! Mutable element access
	T& operator[](const Index i) 
	{
		ASSERT( i < n );
		return data[i];
	}

	//! Immutable element access
	const T& operator[](const Index i) const 
	{
		ASSERT( i < n );
		return data[i];
	}

	//! Bidirectional iterator
	class Iterator
	{
	public:

		//! Constructs a non-associated iterator
		Iterator():d_ptr(NULL){}

		//! Constructs an iterator and associates it with the address `start'
		Iterator(T* start):d_ptr(start){}

		//! Copies internal reference (shallow copy)
		Iterator(const Iterator& other){ d_ptr = other.d_ptr; }

		~Iterator(){}

		//! Assigns internal ref held by `other' iterator (shallow copy)
		Iterator& operator=(const Iterator& other)
		{
			if(&other==this) return *this;
			d_ptr = other.d_ptr;
			return *this;
		}

		//! Comparison operator; true when both iterators point to the same element
		bool operator==(const Iterator& other) { return d_ptr==other.d_ptr; }

		//! Returns false when both iterators point to the same element
		bool operator!=(const Iterator& other) {return d_ptr!=other.d_ptr; }

		//! pre-fix increment: ++it
		Iterator& operator++()
		{
			ASSERT(d_ptr);
			++d_ptr;
			return *this;
		}

		//! pre-fix decriment: --it
		Iterator& operator--()
		{
			ASSERT(d_ptr);
			--d_ptr;
			return *this;
		}

		//! post-fix increment: it++
		Iterator operator++(int)
		{
			Iterator tmp(*this);
			++(*this);
			return tmp;
		}

		//! post-fix decriment: it--
		Iterator operator--(int)
		{
			ASSERT(d_ptr);
			Iterator tmp(*this);
			--(*this);
			return *this;
		}

		//! Dereference operator
		T& operator*() 
		{
			ASSERT(d_ptr);
			return *d_ptr;
		}

	private:

		T* d_ptr;

	};

	//! Returns iterator pointing to the first element
	Iterator begin() {return Iterator(data);}

	//! Returns an iterator pointing to +1 past end
	Iterator end() {return Iterator(data+n);}

	//! Returns an iterator pointing to the last element
	Iterator rbegin() {return Iterator(data+n-1);}

	//! Returns an iterator pointing to +1 before the first element
	Iterator rend() {return Iterator(data-1);}


protected:

	T* data; //*!< internal data array */

	Size n; //*!< number of elements in the array */

};

}//::numlib

#endif
