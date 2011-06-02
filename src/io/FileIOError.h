/*! \file FileIOError.h
 */

#ifndef FILEIOERROR_H
#define FILEIOERROR_H

#include "RodymolError.h"

namespace rodymol
{

class FileIOError: public RodymolError
{
public:
	 
	 FileIOError(const char* errmsg="Failure during file IO"):
		  RodymolError(errmsg) {}

	 FileIOError(const FileIOError & other):
		  RodymolError(other) {}

	 virtual
	 ~FileIOError() throw() {}

	 FileIOError & operator=(const FileIOError & other)
     {
		  RodymolError::operator=(other);
		  return *this;
	 }

};

}

#endif
