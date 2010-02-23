/*! \file DivisionByZero.h
 *  \brief Contains exception for division by zero
 */

#ifndef DIVBYZERO_H
#define DIVBYZERO_H

#include "NumLibError.h"

namespace numlib{

//! Exception denoting the occurance of division by zero
class DivisionByZero: public NumLibError
{
public:

	DivisionByZero(const char* errmsg="Division by zero"):
		NumLibError(errmsg) {}

	DivisionByZero(const DivisionByZero & other):
		NumLibError(other) {}

	virtual
	~DivisionByZero() throw() {}

	DivisionByZero & operator=(const DivisionByZero& other)
	{
		NumLibError::operator=(other);
		return *this;
	}

};

}//::numlib

#endif
