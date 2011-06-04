/*! \file FileIOError.h
 */

#ifndef FILEIOERROR_H
#define FILEIOERROR_H

#include "../base/NumLibError.h"

namespace numlib{ namespace io{

class FileIOError: public NumLibError
{
public:
	 
	 FileIOError(const char* errmsg="Failure during file IO"):
		  NumLibError(errmsg) {}

	 FileIOError(const FileIOError & other):
		  NumLibError(other) {}

	 virtual
	 ~FileIOError() throw() {}

	 FileIOError & operator=(const FileIOError & other)
     {
		  NumLibError::operator=(other);
		  return *this;
	 }

};

}}//::numlib::io

#endif
