/*! \file NumLibException.h
 *  \brief NumLib standard exceptoin definition
 */

#ifndef NUMLIBERROR_H
#define NUMLIBERROR_H

#include <exception>

namespace numlib{

//! Standard NumLib Error
/*!
 *	All NumLib exceptions which indicate an error should derive from this 
 *	class. This will enable all exceptions thrown by NumLib components to
 *	be caught in a single ``catch'' block if so desired. For example,
 *	if NumLib is integrated into a larger analysis suite/framework, 
 *	it may be desirable to parse exceptions based on which library it 
 *	originated from.
 */
class NumLibError: public std::exception
{
	virtual const char* what() const throw()
	{
		return "NumLib error";
	}
};

} //::numlib

#endif
