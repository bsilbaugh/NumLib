/*! \file VectorExpressions.h
 */

#ifndef VECTOREXPRESSIONS_H
#define VECTOREXPRESSIONS_H

#include <iostream>
#include "Vector.h"

namespace numlib{ namespace linalg{

    /*** IO utilities ***/

template<class T>
std::ostream & operator<<(std::ostream & os, const Vector<T> & u)
{
	 for(Index i=0; i<u.size()-1; ++i)
	 {
		  os<<u(i)<<" ";
	 }
	 os<<u(u.size()-1);
	 return os;
}


    /*** partitioning utilities ***/

//! Copies a contiguous range of elements from vector u into vector up
/*!
 *  Per C iteration conventions, 'first' is the index of the first element, 
 *  and 'last' is the index of the last element plus 1; thus, the size of
 *  the partition is 'last' - 'first'.
 *
 *  This isn't a very efficient vector partitioning scheme, but it is
 *  quite robust and safe.
 */
template<class T>
void getPartition(const Vector<T> & u, Vector<T> & up, Index first, Index last)
{
	 ASSERT( last <= u.size() );
	 ASSERT( first <= last );

	 Size n = last - first;

	 if( up.size() != n ) 
		  up.resize(n);

	 for(Index i=0; i<n; ++i)
		  up(i) = u(first + i);
}

//! Copies all of the elements in vector up into a contiguous range of vector u
/*!
 *  Per C iteration conventions, 'first' is the index of the first element, 
 *  and 'last' is the index of the last element plus 1; thus, the size of
 *  the partition is 'last' - 'first'.
 *
 *  This isn't a very efficient vector partitioning scheme, but it is
 *  quite robust and safe.
 */
template<class T>
void setPartition(Vector<T> & u, const Vector<T> & up, Index first, Index last)
{
	 ASSERT( last <= u.size() );
	 ASSERT( first <= last );

	 Size n = last - first;
	 
	 ASSERT( up.size() == n );

	 for(Index i=0; i<n; ++i)
		  u(first + i) = up(i);
}

    /*** Norm Operators ***/

template<class T>
T norm2(const Vector<T> & u)
{
  T val(0);
  T ui;
  for(Index i=0; i<u.size(); ++i)
  {
	  ui = u(i);
	  val += ui*ui;
  }
  return std::sqrt(val);
}

template<class T>
Vector<T> abs(const Vector<T> & u)
{
	 Vector<T> tmp(u.size());
	 for(Index i=0; i<u.size(); ++i)
		 tmp(i) = std::fabs(u(i));
	 return tmp;
}

	/*** Vector-Scalar operations ***/

template<class T> inline
Vector<T> operator*(const Vector<T> & u, const T & c)
{
  Vector<T> tmp(u);
  tmp *= c;
  return tmp;
}

template<class T> inline
Vector<T> operator*(const T & c, const Vector<T> & u)
{
  Vector<T> tmp(u);
  tmp *= c;
  return tmp;
}

template<class T> inline
Vector<T> operator/(const Vector<T> & u, const T & c)
{
  Vector<T> tmp(u);
  tmp /= c;
  return tmp;
}

	/*** Vector-Vector operations ***/

template<class T> inline
Vector<T> operator+(const Vector<T> & u, const Vector<T> & v)
{
  ASSERT( u.size() == v.size() );
  Vector<T> tmp(u);
  tmp += v;
  return tmp;
}

template<class T> inline
Vector<T> operator-(const Vector<T> & u, const Vector<T> & v)
{
  ASSERT( u.size() == v.size() );
  Vector<T> tmp(u);
  tmp -= v;
  return tmp;
}

template<class T>
T prod(const Vector<T> & u, const Vector<T> & v)
{
  ASSERT( u.size() == v.size() );
  T tmp(0);
  for(Index i=0; i<u.size(); ++i)
	tmp += u(i)*v(i);
  return tmp;

  /* NOTE: An alternative implementation would be to use the array product
   * operator to generate a temporary array, and then use the array sum
   * function. This would facilitate code reuse and maintainability, however,
   * it requires the temporary allocation of a potentially large array. The
   * above implementation was chosen to avoid this temporary array
   */
}

}}//::numlib::linalg

#endif
