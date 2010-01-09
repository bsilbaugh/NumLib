/*! \file debug_tools.h
 *  \brief A collection of debugging macro utiltilies
 *
 *  Debugging assertions are activated when DEBUG is defined. Debug
 *  print statements are activated when DEBUG is set to a value
 *  greater than 1.
 *
 */

#ifndef DEBUG_TOOLS_H
#define DEBUG_TOOLS_H

#include <iostream>
#include <fstream>
#include "NumLibError.h"

//! Prints msg to STDOUT if DEBUG set to a value greater than 1
#if DEBUG>1
#define DEBUG_PRINT( msg) \
	std::cout<< "(debug print: file " << __FILE__ << ", line no "<<  __LINE__ << ") \n\t" << msg <<std::endl;
#else
#define DEBUG_PRINT( msg )
#endif

//! Prints the name of a variable and its value to STDOUT
#define DEBUG_PRINT_VAR( var ) \
	DEBUG_PRINT( #var << " = " << var )

//! Streams variable values to output log file
/*!
 *  Each call to DEBUG_LOG results in a new entry to the log file.
 *  Each entry to the log file is appended as a new line by using 
 *  the overloaded stream insertion operator (operator<<).
 */
#if DEBUG>2
#define DEBUG_LOG( log_file_name, var ) \
	append_to_log(log_file_name, var)
#else
#define DEBUG_LOG(log_file_name, var)
#endif

//! Prints error to STDOUT and throws if statement evaluates to false
#ifndef DEBUG
#define ASSERT( statement )
#else
#define ASSERT( statement )						                     \
	 if ( !(statement) )											 \
	 {																 \
		std::cerr << "\nERROR Assert " << #statement << " failed\n"; \
		std::cerr << "on line " << __LINE__ << "\n";				 \
		std::cerr << "in file " << __FILE__ << "\n\n";				 \
		exit(EXIT_FAILURE);											 \
	}
#endif

template<class T>
void append_to_log(const char* log_file_name, T var)
{
	std::ofstream log_file;
	log_file.open(log_file_name, std::ios_base::app);
	log_file<<var<<std::endl;
	log_file.close();
}

#endif
