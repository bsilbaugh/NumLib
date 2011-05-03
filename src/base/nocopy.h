/*! \brief Macros for disabling copy and assignment
 */

#ifndef NOCOPY_H
#define NOCOPY_H

//! A macro to disallow the copy constructor and operator= functions
/*!
 *  For many object classes, it is more appropriate to create multiple
 *  references/pointers to the same entity instead of creating a copy.
 *  In such cases, the copy and assignment operators need to be explicitly
 *  dissabled.
 *
 *	To disable copy and assignment, place  this macro in the private 
 *	section of a class declaration. If a copy or assignment operation is 
 *	attempted somewhere in the code a compilation error should occur.
 *
 *	This procedure for disabling copy and assignment was taken from the
 *	Google C++ Style Guide (rev 3.127).
 */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) 	\
	TypeName(const TypeName&); 				\
	TypeName& operator=(const TypeName&)

//! A macro to disable object assignment operator
/*!
 *	This is useful in situations where it is desirable to restrict
 *	duplication of objects to cloning operations only.
 *
 *	To disable assignment, place this macro in the private
 *	section of a class declaration. Any subsequent attempt to 
 *	execute assignment will result in a compilation error.
 */
#define DISALLOW_ASSIGN(TypeName) 	\
	TypeName& operator=(const TypeName&)

#endif
