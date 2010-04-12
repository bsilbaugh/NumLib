/*! \file factorial.h
 */

#ifndef FACTORIAL_H
#define FACTORIAL_H

#include "numlib-config.h"

namespace numlib{

//! Recursive factorial function for integer type Int
inline
Int factorial(const Int& k)
{
	if(x==0)
		return k;
	return k*factorial(k-1);
}

}//::numlib

#endif
