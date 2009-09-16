/*! \file reconstruction.cpp
 */

/*** THIS IMPLEMENTATION IS NOT FINAL ***/

#include <boost/python.hpp>
#include "numlib/array/Array1D.h"
#include "numlib/reconstruction/LinearPW.h"

using namespace numlib;

typedef numlib::array::Array1D<Real> Grid;
typedef numlib::array::Array1D<Real> Field;
typedef numlib::reconstruction::LinearPW<Grid, Field> LinearPW;

Field interpolate(LinearPW& self, const Field& src)
{
	Field dst(src.size());
	self(src, dst);
	return dst;
}

BOOST_PYTHON_MODULE( _reconstruction )
{

	using namespace boost::python;

	class_< LinearPW >("LinearPW", init< const Grid&, const Grid& >())
		.def("__call__", &interpolate)
	;
}
