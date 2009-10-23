/*! \file reconstruction.cpp
 */

/*** THIS IMPLEMENTATION IS NOT FINAL ***/

#include <boost/python.hpp>
#include "numlib/array/Array1D.h"
#include "numlib/tensor/TensorR1.h"
#include "numlib/tensor/TensorR2.h"
#include "numlib/reconstruction/LinearPW.h"
#include "numlib/reconstruction/RotInterp.h"

using namespace numlib;
using numlib::tensor::TensorR1;
using numlib::tensor::TensorR2;

typedef numlib::array::Array1D<Real> Grid1D;
typedef numlib::array::Array1D<Real> ScalarField1D;
typedef numlib::array::Array1D<TensorR1> VectorField1D;
typedef numlib::array::Array1D<TensorR2> TensorField1D;
typedef numlib::reconstruction::LinearPW<Grid1D, ScalarField1D> ScalarInterp;
typedef numlib::reconstruction::LinearPW<Grid1D, VectorField1D> VectorInterp;
typedef numlib::reconstruction::RotInterp<Grid1D, TensorField1D> RotationInterp;

template<class I, class F>
void interpolate(I& self, const F& src, F& dst)
{
	self(src, dst);
}

BOOST_PYTHON_MODULE( _reconstruction )
{

	using namespace boost::python;

	class_< ScalarInterp >("ScalarInterp", init< const Grid1D&, const Grid1D& >())
		.def("__call__", &interpolate<ScalarInterp, ScalarField1D>)
	;

	class_< VectorInterp >("VectorInterp", init< const Grid1D&, const Grid1D& >())
		.def("__call__", &interpolate<VectorInterp, VectorField1D>)
	;

	class_< RotationInterp >("RotationInterp", init< const Grid1D&, const Grid1D& >())
		.def("__call__", &interpolate<RotationInterp, TensorField1D>)
	;

}
