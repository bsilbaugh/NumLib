/*! \file SharedPtr.h
 */

#ifndef SHAREDPTR_H
#define SHAREDPTR_H

namespace numlib{ namespace smartptr{

//! Smart pointer template which implements reference counting
/*!
 *  Good Example:
 *    SharedPtr<Foo> p1(new Foo()); // First ref to foo
 *    ... (more code) ...
 *    SharedPtr<Foo> p2 = p1;       // Second ref to foo, ref count incremented
 *
 *  Bad Example:
 *    Foo* p = new Foo;
 *    ... (more code) ...
 *    SharedPtr<Foo> p1(p); // allowed by compiler
 *    ... (more code) ...
 *    SharedPtr<Foo> p2(p); // now have duplicate ref count => memory error
 *
 */
template< class T>
class SharedPtr
{
public:

  //! Creates a null pointer
  SharedPtr():ptr(0),ref_count(0){}

  //! Creates a pointer to a *newly* created object of type T
  SharedPtr(T* object):ptr(object),ref_count(new Size)
  {
	*ref_count = 1;
  }

  //! Copy constructor - ref count to pointed object incremented
  SharedPtr(const SharedPtr<T> & other):ptr(other.ptr),ref_count(other.ref_count)
  {
	incref();
  }

  //! Destructor - ref count to pointed object decremented
  /*!
   *  If after decrementing the reference count, the reference count is
   *  zero, the referenced object will be deleted.
   */
  ~SharedPtr() {decref()}

  //! Obtaines reference to object pointed to by "other" and increments ref count
  /*!
   *  If a reference to another object is held prior to assignment, then the 
   *  reference count to the original object will be decremented prior to 
   *  obtaining a reference to the new object implied by assignment operation.
   *
   */
  SharedPtr & operator=(const SharedPtr<T> & other)
  {
	// Decriment current reference, if any...

	if(ptr) decref();

	// Aquire new reference and its ref count...

	ptr = other.ptr;
	ref_count = other.ref_count;

	// Increment ref count...

	incref();

  }

  //! Indirection operator
  T* operator->() {return ptr;}

  //! Dereference operator
  T& operator*() {return *ptr;}

private:

  //! Pointer to shared object
  T* ptr;

  //! Pointer to reference count
  Size* ref_count;

  //! Increments ref count
  void incref()
  {
	++(*ref_count);
  }

  //! Decriments ref count and deletes object if count becomes zero
  void decref()
  {
	--(*ref_count);
	if(*ref_count == 0)
	  {
		DEBUG_PRINT( "ref count is zero - deleting object" );
		delete ptr; ptr=0;
		delete ref_count; ref_count=0;
	  }
  }

};

}}//::numlib::smartptr

#endif
