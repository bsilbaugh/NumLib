/*! \file tensor.cpp
 *  \brief Python bindings for numlib::tensor
 */

#include <boost/python.hpp>
#include "numlib/tensor/TensorR1.h"
#include "numlib/tensor/TensorR2.h"
#include <sstream>

using namespace numlib;
using namespace numlib::tensor;

//! Checks component index limits
static
void check_bounds(Index i)
{
	using namespace boost::python;

	if( (i < 1) or (i > 3) )
	{
		PyErr_SetString(PyExc_KeyError, "Index must be 1, 2, or 3");
		throw_error_already_set();
	}
}

namespace tensorR1_wrap
{

	//! Extracts string representation of TensorR1
	const char* print(const TensorR1& u)
	{
		std::ostringstream ss;
		ss<<"( "<<u(1)<<", "<<u(2)<<", "<<u(3)<<" )";
		return ss.str().c_str();
	}

	//! Returns ith component value
	Real get_component(const TensorR1& self, const Index i)
	{
		check_bounds(i);
		return self(i);
	}

	//! Sets value of ith component
	void set_component(TensorR1& self, const Index i, const Real val)
	{
		check_bounds(i);
		self(i) = val;
	}

}//::tensorR1_wrap

namespace tensorR2_wrap
{
	const char* print(const TensorR2& u)
	{
		std::ostringstream ss;
		ss<<" "<<u(1,1)<<", "<<u(1,2)<<", "<<u(1,3)<<"\n";
		ss<<" "<<u(2,1)<<", "<<u(2,2)<<", "<<u(2,3)<<"\n";
		ss<<" "<<u(3,1)<<", "<<u(3,2)<<", "<<u(3,3);
		return ss.str().c_str();
	}

	Real get_component(const TensorR2& self, boost::python::tuple key)
	{
		using namespace boost::python;
		Index i = extract<int>(key[0]);
		Index j = extract<int>(key[1]);
		check_bounds(i);
		check_bounds(j);
		return self(i,j);
	}

	void set_component(TensorR2& self, const boost::python::tuple key, const Real val)
	{
		using namespace boost::python;
		Index i = extract<int>(key[0]);
		Index j = extract<int>(key[1]);
		check_bounds(i);
		check_bounds(j);
		self(i,j) = val;
	}

}//::tensorR2_wrap

/*** overloads ***/

Real (*dot_o1)(const TensorR1&, const TensorR1&) = &dot;
TensorR1 (*dot_o2)(const TensorR2&, const TensorR1&) = &dot;
TensorR1 (*dot_o3)(const TensorR1&, const TensorR2&) = &dot;

TensorR1 (*cross_o1)(const TensorR1&, const TensorR1&) = &cross;

Real (*norm_o1)(const TensorR1&) = &norm;

Real (*trace_o1)(const TensorR2&) = &trace;

/*** python module ***/

BOOST_PYTHON_MODULE( _tensor )
{
	using namespace boost::python;

	// Create python bindings for tensor types...

	class_<TensorR1>("TensorR1")
		.def(init<Real, Real, Real>())
		.def("__str__", &tensorR1_wrap::print)
		.def("__getitem__", &tensorR1_wrap::get_component)
		.def("__setitem__", &tensorR1_wrap::set_component)
		.def( self += other<TensorR1>() )
		.def( self -= other<TensorR1>() )
		.def( self *= other<Real>() )
		.def( self /= other<Real>() )
		;

	class_<TensorR2>("TensorR2")
		.def(init<Real, Real, Real, Real, Real, Real, Real, Real, Real>())
		.def("__str__", &tensorR2_wrap::print)
		.def("__getitem__", &tensorR2_wrap::get_component)
		.def("__setitem__", &tensorR2_wrap::set_component)
		.def( self += other<TensorR2>() )
		.def( self -= other<TensorR2>() )
		.def( self *= other<Real>() )
		.def( self /= other<Real>() )
	;

	// Wrap overloaded functions...

	def("dot", dot_o1);
	def("dot", dot_o2);
	def("dot", dot_o3);

	def("cross", cross_o1);

	def("norm", norm_o1);

	def("trace", trace_o1);

}
