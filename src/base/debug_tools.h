/*! \file debug_tools.h
 *  \brief A collection of debugging macro utiltilies
 *
 *  To activiate all debugging macros define DEBUG.
 *
 */

#ifndef DEBUG_TOOLS_H
#define DEBUG_TOOLS_H

#include <iostream>
#include "NumLibError.h"

//! Prints msg to STDOUT
#ifndef DEBUG
#define DEBUG_PRINT( msg )
#else
#define DEBUG_PRINT( msg) \
	std::cout<< "(debug print: file " << __FILE__ << ", line no "<<  __LINE__ << ") " << msg <<std::endl;
#endif

//! Prints the name of a variable and its value to STDOUT
#define DEBUG_PRINT_VAR( var ) \
	DEBUG_PRINT( #var << " = " << var )

//! Prints error to STDOUT and throws if statement evaluates to false
#ifndef DEBUG
#define ASSERT( statement )
#else
#define ASSERT( statement ) \
	if ( !(statement) ) \
    { \
		std::cout << "\nERROR Assert " << #statement << " failed\n"; \
		std::cout << "on line " << __LINE__ << "\n"; \
		std::cout << "in file " << __FILE__ << "\n\n"; \
		throw NumLibError();						   \
	}
#endif

#endif
