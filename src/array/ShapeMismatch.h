/*! \file ShapeMismatch.h
 *  \brief Contains exception for mismatched array shapes
 */

#ifndef SHAPEMISMATCH_H
#define SHAPEMISMATCH_H

#include "../base/NumLibError.h"

namespace numlib{ namespace array{

//! Mismatched array shape exception
/*! 
 *  Exception to be throw when attempting to perform an operation
 *  on arrays of different shape.
 */
class ShapeMismatch: public numlib::NumLibError
{
	virtual const char* what() const throw()
	{
		return "NumLib error: Array shapes do not match";
	}
};

}} // ::numlib::array
#endif
