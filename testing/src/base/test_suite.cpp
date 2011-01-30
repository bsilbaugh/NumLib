/*! \file base-test_suite.cpp
 *  \brief Unit test suite for NumLib base.
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "numlib/base/numlib-config.h"
#include "numlib/base/constants.h"
#include "numlib/base/factorial.h"
#include "numlib/base/random.h"

using namespace numlib;

BOOST_AUTO_TEST_SUITE( base )

BOOST_AUTO_TEST_CASE( abs )
{
	Real x = -1.516873;
	BOOST_CHECK( 1.0 + numlib::abs(x) + x == 1.0 );
}

BOOST_AUTO_TEST_CASE( is_zero )
{
	Real x = 1.516873;
	BOOST_CHECK(  numlib::is_zero(x-x) );
	BOOST_CHECK( !numlib::is_zero(x+x) );
	BOOST_CHECK( !numlib::is_zero(0.005) );
}

BOOST_AUTO_TEST_CASE( factorial )
{
	BOOST_CHECK_EQUAL( numlib::factorial(0),        1);
	BOOST_CHECK_EQUAL( numlib::factorial(1),        1);
	BOOST_CHECK_EQUAL( numlib::factorial(2),        2);
	BOOST_CHECK_EQUAL( numlib::factorial(3),        6);
	BOOST_CHECK_EQUAL( numlib::factorial(4),       24);
	BOOST_CHECK_EQUAL( numlib::factorial(5),      120);
	BOOST_CHECK_EQUAL( numlib::factorial(6),      720);
	BOOST_CHECK_EQUAL( numlib::factorial(7),     5040);
	BOOST_CHECK_EQUAL( numlib::factorial(8),    40320);
	BOOST_CHECK_EQUAL( numlib::factorial(9),   362880);
	BOOST_CHECK_EQUAL( numlib::factorial(10), 3628800);

}

BOOST_AUTO_TEST_CASE( random )
{
	for(Index i=0; i<10; ++i)
	{
		Real x = numlib::randomNumber();
		BOOST_CHECK_LT( x , 1.0 );
		BOOST_CHECK_GT( x , 0.0 );
	}
}

BOOST_AUTO_TEST_CASE( pi_value )
{
	BOOST_CHECK_CLOSE(pi, 
			3.14159265358979323846264338327950288419716939937510,
			0.005);

	Real pi_true = 3.14159265358979323846264338327950288419716939937510;
	BOOST_CHECK( 1.0+pi-pi_true==1.0 );
}

BOOST_AUTO_TEST_CASE( twopi_value )
{
	Real twopi_true = pi + pi;
	BOOST_CHECK(1.0+twopi-twopi_true==1.0);
}

BOOST_AUTO_TEST_CASE( deg_to_rad_value )
{
	BOOST_CHECK( 1.0+deg_to_rad-pi/180.0==1.0 );
}

BOOST_AUTO_TEST_CASE( rad_to_deg_value )
{
	BOOST_CHECK( 1.0+rad_to_deg-180.0/pi==1.0 );
}

BOOST_AUTO_TEST_SUITE_END()
