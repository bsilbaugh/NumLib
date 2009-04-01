
#ifndef IO_H
#define IO_H

#include <iostream>
#include <iomanip>

#include "numlib-config.h"

namespace numlib{

//! Formats printing of Real numbers
/*! 
 *	THIS CONFLICTS WITH STL DEF -- DO NOT USE -- NEEDS TO BE FIXED
 */
inline
std::ostream & operator<<(std::ostream & os, const Real & x)
{
	os<<std::scientific<<std::setw(16)<<std::setprecision(8)<<x;
	return os;
}

} //::numlib

#endif
