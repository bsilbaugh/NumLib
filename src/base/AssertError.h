/*! \file AssertError.h
 *  \brief Assertion error
 */

#ifndef ASSERTERROR_H
#define ASSERTERROR_H

#include <exception>

//! Basic assertion error
class AssertError: public std::exception
{
	virtual const char* what() const throw()
	{
		return "Assertion failed";
	}
};

#endif
