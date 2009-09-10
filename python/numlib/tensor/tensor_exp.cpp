/*! \file tensor_exp.cpp
 *  \brief Python bindings for experimental tensor field types
 *
 *  Both AML and Rodymol currently use an ad-hoc implementation of
 *  scalar, vector, and tensor fields based on Array1D. This module
 *  provides a common set of python bindings for these types. Thistensor types
 *  particular implementation is not part of the "official" NumLib
 *  library since Array1D implements operations that are not
 *  strickly defined for such field types (e.g. division of a
 *  vector field by another vector field). Once, proper field types
 *  have been implemented, this module can be dumped.
 */

#include <boost/python.hpp>
#include "../array/wrap_Array1D.h"
#include "numlib/array/Array1D.h"
#include "numlib/tensor/TensorR1.h"
#include "numlib/tensor/TensorR2.h"

#define WRAP_FIELD1D( Val, PyName )                                     \
	class_< Array1D<Val> >( #PyName ) 									\
		.def(init<numlib::Size>())												\
		.def("resize", &Array1D<Val>::resize) 							\
		.def("__len__", &Array1D<Val>::size) 							\
		.def("__getitem__", &ArrayItem<Val>().get,  					\
					return_value_policy<copy_non_const_reference>() )   \
		.def("__setitem__", &ArrayItem<Val>().set) 						\

BOOST_PYTHON_MODULE( _tensor_exp )
{
	using namespace boost::python;

	WRAP_FIELD1D( numlib::Real, ScalarField1D );
	WRAP_FIELD1D( numlib::tensor::TensorR1, VectorField1D );
	WRAP_FIELD1D( numlib::tensor::TensorR2, TensorField1D );
}
