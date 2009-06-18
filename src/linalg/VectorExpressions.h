/*! \file VectorExpressions.h
 */

#ifndef VECTOREXPRESSIONS_H
#define VECTOREXPRESSIONS_H

#include "Vector.h"

namespace numlib{ namespace linalg{

    /*** Norm Operators ***/

template<class T>
T norm2(const Vector<T> & u)
{
  T tmp( sum(u.data*u.data) );
  return std::sqrt(tmp);
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
