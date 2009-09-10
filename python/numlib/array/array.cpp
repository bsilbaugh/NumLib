/*! \file array.cpp
 *  \brief Python bindings for the NumLib Array library
 *  
 *  \todo Add a factory function (e.g. Array( ElemType ) ) which
 *  generates an array of appropriate type in python. This would
 *  avoid the need for the python user to track the mangled array
 *  names; e.g. in python the syntax would be
 *
 * 	>>> a = Array1D("Real") 
 *
 *  instead of 
 *
 * 	>>> a = RealArray1D()
 */

#include <boost/python.hpp>
#include "numlib/array/Array1D.h"
#include "wrap_Array1D.h"

BOOST_PYTHON_MODULE( _array )
{
	using namespace boost::python;

	WRAP_ARRAY1D( numlib::Real, RealArray1D );
	WRAP_ARRAY1D( numlib::Index, IndexArray1D );

}
