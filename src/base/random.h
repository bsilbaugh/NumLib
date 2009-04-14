/*! \file random.h
 *  \brief Functions for generating random floating point numbers
 *
 *  This basically extends the random number functions provided in
 *  the C++ standard library to generate floating point numbers 
 *  instead of integer values.
 */

#ifndef RANDOM_H
#define RANDOM_H

#include "numlib-config.h"
#include <cstdlib>
#include <ctime>

namespace numlib{

//! Seeds random number generator using current time
inline
void randomSeed()
{
	std::srand((unsigned)std::time(0));
}

//! Generates a floating point random number between 0.0 and 1.0
inline
Real randomNumber()
{
	int random_int = std::rand();
	return ((Real)random_int)/(Real)RAND_MAX;
}

}

#endif
