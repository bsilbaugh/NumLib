/*! \file IndexError.h
 *  \brief IndexError exception definition
 */

#ifndef INDEXERROR_H
#define INDEXERROR_H

#include "NumLibError.h"

namespace numlib{

class IndexError: public NumLibError
{
	virtual const char* what() const throw()
	{
		return "NumLib error: Bad index";
	}
};

}

#endif
