/*! \file TriMatrixExpressions.h
 */

#include "Vector.h"
#include "TriMatrix.h"

namespace numlib{ namespace linalg{

template<class T>
Vector<T> prod(const TriMatrix<T> & a, const Vector<T> & u)
{
  ASSERT(u.size() == a.size1());
  Size n = u.size();
  T zero(0);
  Vector<T> v(n);

  for(Index i=0; i<n; ++i)
	v(i) = a.diagBand(i)*u(i);

  for(Index i=0; i<n-1; ++i)
  {
	v(i+1) += a.lowerBand(i+1)*u(i);
	v(i) += a.upperBand(i)*u(i+1);
  }

  return v;

}

}}//::numlib::linalg
