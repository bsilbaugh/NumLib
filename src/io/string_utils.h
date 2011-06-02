/*! \file string_utils.h
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <sstream>
#include <iostream>
#include "rodymol-config.h"

namespace rodymol
{

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

//! A utility for striping all white-space from a std::string
/*!
 *  The string is modified in-place.
 */
void stripWhiteSpace(String & s, const char* whitespace=" \t");

//! A utility for stripping comment lines from string
void stripComments(String & s, char cc='#');

}//::rodymol

#endif
