
#ifndef IO_H
#define IO_H

#include <iostream>
#include <iomanip>

#include "numlib-config.h"

namespace numlib{

//! Manipulator for formatting output of Real types
inline
std::ostream & fmtReal(std::ostream & os)
{
	 return os<<std::scientific<<std::setprecision(8)<<std::setw(15);
}

}

#endif
