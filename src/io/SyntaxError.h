/*! \file SyntaxError.h
 */

#ifndef SYNTAXERROR_H
#define SYNTAXERROR_H

#include "RodymolError.h"

namespace rodymol
{

class SyntaxError: public RodymolError
{
public:
	 
	 SyntaxError(const char* errmsg="Unrecognized syntax in input stream"):
		  RodymolError(errmsg) {}

	 SyntaxError(const SyntaxError & other):
		  RodymolError(other) {}

	 virtual
	 ~SyntaxError() throw() {}

	 SyntaxError & operator=(const SyntaxError & other)
     {
		  RodymolError::operator=(other);
		  return *this;
	 }
};

}

#endif
