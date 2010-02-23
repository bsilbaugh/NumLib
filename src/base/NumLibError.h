/*! \file NumLibError.h
 */

#ifndef NUMLIBERROR_H
#define NUMLIBERROR_H

#include<exception>
#include<sstream>
#include<cstring>
#include<string>

namespace numlib
{

//! Generic exception class which indicates a run-time error
/*!
 * 	Custom exception derived from the standard libary exception class.
 * 	NumLibError extends std::exception by storing an error message when 
 * 	invoking throw; e.g.
 *
 * 		throw NumLibException("A useful error message")
 *
 *
 *  Since NumLibError is derived from std::exception, a generic exception
 *  handler looking for a member of std::exception will catch this
 *  exception; e.g. the following should work: 
 *
 *  	try{
 *  		foo(); // Throws an exception of type NumLibException
 *		}  		
 *  	catch(std::exception & e){
 *  		std::cout<<e.what();	//Catches NumLibException;
 *  	}
 *
 *  Note that this is a generic exception class. This means that the
 *  exception handler will not be able to identify the nature of the
 *  exception. At best, the exception handler will simply know that 
 *  something has gone wrong and a unique message is attached. If you 
 *  wish specific action to be taken by the error handler (besides 
 *  printing a message and stopping excecution), use an appropriate
 *  exception subclass which represents the specific exception condition;
 *  e.g. FileIOError, SyntaxError, etc
 */
class NumLibError: public std::exception
{
public:
    
	 //! Message constructor
	 NumLibError(const char* errmsg="NumLib Error");
    
	 //! Copy constructor
	 NumLibError(const NumLibError & other);

	 //! Destructor
	 virtual 
	 ~NumLibError() throw();
    
	 //! Assignment operator
	 NumLibError & operator=(const NumLibError & other);

	 //! override "what()" method of std exception class
	 virtual 
	 const char* what() const throw();

private:
    
	 char *msg;
    
};

}//::numlib

#endif
