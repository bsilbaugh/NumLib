/*! \file stream_utils.h
 */

#ifndef STREAM_UTILS_H
#define STREAM_UTILS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "string_utils.h"
#include "FileIOError.h"
#include "SyntaxError.h"
#include "CompModelNameList.h"
#include "ConnInstSet.h"

namespace rodymol
{

//! Manipulator for formatting output of Real types
inline
std::ostream & fmtReal(std::ostream & os)
{
	 return os<<std::scientific<<std::setprecision(6)<<std::setw(15);
}

//! stream insertion operator for string dictionary types
std::ostream & operator<<(std::ostream & os, const Dict & dict);

//! stream insertion operator for real lists
std::ostream & operator<<(std::ostream & os, const RealList & list);

//! stream insertion operator for size lists
std::ostream & operator<<(std::ostream & os, const SizeList & list);

//! Extracts a TensorR1 from input stream
std::istream & operator>>(std::istream & is, TensorR1 & u);

//! Extracts Euler rotation parameter vectro from input stream
std::istream & operator>>(std::istream & is, EulerParameterVector & u);

//! Extracts a TensorR2 from input stream
std::istream & operator>>(std::istream & is, TensorR2 & u);

//! Opens an input file stream an verifies association with file
void open(const String & fileName, std::ifstream & is);

//! Opens an output file stream for output
void open(const String & fileName, std::ofstream & os);

//! Loads ASCII input file and strips all whitespace and comment lines
/*!
 *  After establishing an file input stream, all comments and whitespace are
 *  stripped from the input stream and returned as a stringstream object.
 *  The file input stream is closed prior to return. Each physical line in
 *  the input file is preserved in the returned stringstream; thus, use of
 *  getline on the returned stringstream will return each input expression
 *  (as a string) in the same order they appeared in the original file.
 */
void loadInputFileASCII(const String & fileName, StringStream & buff);

//! Parses config input stream
void parseInputStream(StringStream & buff, Dict & dict, const char* delim="=");

//! Parses component model name list
void parseCompModelNameList(StringStream & buff, CompModelNameList & nameList);

//! Parses connectivity input stream
void parseConnInst(StringStream & buff, 
				   ConnInstSet & cisPointLinear,
				   ConnInstSet & cisPointRotational,
				   ConnInstSet & cisCurveLinear,
				   ConnInstSet & cisCurveRotational);

}//::rodymol

#endif
