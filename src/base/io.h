
#ifndef IO_H
#define IO_H

#include <iostream>
#include <iomanip>

#include "numlib-config.h"

namespace numlib{

//! Manipulator for formatting output of Real types
inline
std::ostream & fmtReal(std::ostream & os)
{
	 return os<<std::scientific<<std::setprecision(8)<<std::setw(15);
}

//! A utility for extracting numeric types from strings
/*!
 *  The third parameter should be one of the following:
 *  - std::hex
 *  - std::dec
 *  - std::oct
 */
template<class T>
bool fromString(T& t, const String & s, std::ios_base& (*f)(std::ios_base&)=std::dec)
{
	 std::istringstream iss(s);
	 return !(iss >> f >> t).fail();
}

}

#endif
