/*! \file NumLibError.cpp
 */

#include "NumLibError.h"

namespace numlib
{

NumLibError::NumLibError(const char* errmsg):std::exception()
{
	 msg = new char[std::strlen(errmsg)];
	 std::strcpy(msg, errmsg);
}

NumLibError::NumLibError(const NumLibError & other):std::exception()
{
	 msg = new char[std::strlen(other.msg)];
	 std::strcpy(msg, other.msg);
}

NumLibError::~NumLibError() throw()
{
	 delete [] msg;
}

NumLibError & NumLibError::operator=(const NumLibError & other)
{
	 if(&other == this) 
		  return *this;

	 msg = new char[std::strlen(other.msg)];
	 std::strcpy(msg, other.msg);

	 return *this;
}

const char* NumLibError::what() const throw()
{
	 return msg;
}


}//::numlib
