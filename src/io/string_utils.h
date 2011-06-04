/*! \file string_utils.h
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include "../base/numlib-config.h"

namespace numlib{ namespace io{

typedef std::string String;

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

//! Overloaded version of fromString to handle special case of T=String
inline
bool fromString(String& t, const String & s)
{
	t=s;
	return true;
}

//! A utility for striping all white-space from a std::string
/*!
 *  The string is modified in-place.
 */
void stripWhiteSpace(String & s, const char* whitespace=" \t");

//! A utility for stripping comment lines from string
void stripComments(String & s, char cc='#');

//! Parses a string into a two substrings
/*!
 * 	Given a string of the form <string1><del><string2>, this function
 * 	returns <string1> and <string2> as substrings. For example, the
 * 	string "key=val", with '=' as the delimeter, will be returned as
 * 	"key" and "val".
 *
 *  Note that it is assumed that all superfluous white space has already
 *  been removed by a function such as stripWhiteSpace.
 *
 *  False is returned if succesfull (i.e. no error), otherwise true is
 *  returned.
 */
bool split(const String& line, String& substr1, String& substr2, const char* delim);

}}//::numlib::io

#endif
