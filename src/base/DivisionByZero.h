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
	virtual char* what() throw()
	{
		return "NumLib error: Division by zero";
	}
};

}

#endif
