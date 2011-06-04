/*! \file SyntaxError.h
 */

#ifndef SYNTAXERROR_H
#define SYNTAXERROR_H

#include "../base/NumLibError.h"

namespace numlib{ namespace io{

class SyntaxError: public NumLibError
{
public:
	 
	 SyntaxError(const char* errmsg="Unrecognized syntax in input stream"):
		  NumLibError(errmsg) {}

	 SyntaxError(const SyntaxError & other):
		  NumLibError(other) {}

	 virtual
	 ~SyntaxError() throw() {}

	 SyntaxError & operator=(const SyntaxError & other)
     {
		  NumLibError::operator=(other);
		  return *this;
	 }
};

}}//::numlib::io

#endif
