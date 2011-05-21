/*! \file Vector.h
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "../array/Array1D.h"

namespace numlib{ namespace linalg{

//! Dense vector model
/*!
 *  Models a dense vector for elements of type T, where type T may be any complete
 *  numerical type.
 */
template<class T>
class Vector
{
public:

   //! Constructs a vector with dimension n
   Vector(Size n_=0);

   //! Copy constructor (deep copy)
   Vector(const Vector & other);

   //! Destructor
   ~Vector();

   //! Assignment (deep copy)
   Vector & operator=(const Vector & other);

   //! Sets all elements to zero
   void zero();

   /* Container interface */

   Size size() const;

   //! Resizes vector to hold n elements
   /*!
	*  Original contents may be destroyed. Resize operation is provided to
	*  facilitate initialization of default constructed vectors.
	*/
   void resize(Size n_);

   T & operator()(Index i);

   const T & operator()(Index i) const;

   /* In-place arithmetic operators */

   Vector & operator*=(const T & c);

   Vector & operator/=(const T & c);

   Vector & operator+=(const Vector & other);

   Vector & operator-=(const Vector & other);

private:

   //! Size
   Size n;
  
   //! element array
   T* data;

};

#include "Vector-inl.h"

}}//::numlib::linalg

#endif
