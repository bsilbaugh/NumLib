/*! \file wrap_Array1D.h
 *  \brief Helper utilities for wrapping Array1D template class
 */

#ifndef WRAP_ARRAY1D_H
#define WRAP_ARRAY1D_H

#include <boost/python.hpp>
#include "numlib/array/Array1D.h"

using numlib::array::Array1D;

//! Checks array bounds -- throws python exception if bounds exceeded
void check_bounds(numlib::Index i, numlib::Size n)
{
	using namespace boost::python;
	
	if( i >= n ) 
	{
		PyErr_SetString(PyExc_KeyError, "Index exceeds array bounds");
		throw_error_already_set();
	}
	else if( i < 0 )
	{
		PyErr_SetString(PyExc_KeyError, "Negative index not allowed");
		throw_error_already_set();
	}
}

//! A generic accessor class to facilitate element access of Array1D
/*!
 *  Implementation is roughly based on the example given in the
 *  boost python wiki. 
 */
template<class T>
struct ArrayItem
{
	typedef numlib::array::Array1D<T> Array;
	typedef numlib::Index Key;
	typedef numlib::Size Size;

	//! Resizes array to contain n elements
	/*!
	 *  Contents of array are not strickly preserved
	 */
	static
	void resize(Array& self, const Size n)
	{
		self.resize(n);
	}

	//! Returns value of ith array element
	static
	T& get(Array& self, const Key i)
	{
		check_bounds(i, self.size());
		return self(i);
	}

	//! Sets value of ith array element
	static
	void set(Array& self, const Key i, const T& val)
	{
		check_bounds(i, self.size());
		self(i) = val;
	}
};

//! Generates boost python class wrapper for Array1D template
/*!
 *  \todo May want to abstract this a bit more to facilitate
 *  wrapping of Array2D, Array3D, etc.
 */
#define WRAP_ARRAY1D( Val, PyName )                                     \
	class_< Array1D<Val> >( #PyName ) 									\
		.def("resize", &Array1D<Val>::resize) 							\
		.def("__len__", &Array1D<Val>::size) 							\
		.def("__getitem__", &ArrayItem<Val>().get,  					\
					return_value_policy<copy_non_const_reference>() )   \
		.def("__setitem__", &ArrayItem<Val>().set) 						\
		.def( self *= other<Val>() ) 									\
		.def( self /= other<Val>() ) 									\
		.def( self += other<Val>() ) 									\
		.def( self -= other<Val>() ) 									\
		.def( self += other< Array1D<Val> >() ) 						\
		.def( self -= other< Array1D<Val> >() ) 						\
		.def( self *= other< Array1D<Val> >() ) 						\
		.def( self /= other< Array1D<Val> >() ) 						\
		.def( self + other<Val>() ) 									\
		.def( self - other<Val>() ) 									\
		.def( self * other<Val>() ) 									\
		.def( self / other<Val>() ) 									\
		.def( self + other< Array1D<Val> >() ) 							\
		.def( self - other< Array1D<Val> >() ) 							\
		.def( self * other< Array1D<Val> >() ) 							\
		.def( self / other< Array1D<Val> >() )

#endif
