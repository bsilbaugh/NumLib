
#ifndef STREAM_MANIP_H
#define STREAM_MANIP_H

#include <iostream>
#include <iomanip>

#include "../base/numlib-config.h"

namespace numlib{ namespace io{

//! Manipulator for formatting output of Real types
inline
std::ostream & fmtReal(std::ostream & os)
{
	 return os<<std::scientific<<std::setprecision(8)<<std::setw(15);
}

}}//::numlib::io

#endif
