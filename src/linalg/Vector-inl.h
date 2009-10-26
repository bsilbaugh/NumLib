/*! \file Vector-inl.h
 */

template<class T>
Vector<T>::Vector(Size n):data(n)
{
}

template<class T>
Vector<T>::Vector(const Vector & other):data(other.data)
{
}

template<class T>
Vector<T>::~Vector()
{
  /* nothing to delete */
}

template<class T>
Vector<T> & Vector<T>::operator=(const Vector & other)
{
  if(&other!=this)
	data = other.data;
  return *this;
}

template<class T>
void Vector<T>::zero()
{
  T zero(0);
  data = zero; /* broadcast zero to all elements */
}

template<class T> inline
Size Vector<T>::size() const
{
  return data.size();
}

template<class T>
void Vector<T>::resize(Size n_)
{
  data.resize(n_);
}

template<class T> inline
T & Vector<T>::operator()(Index i)
{
  return data(i);
}

template<class T> inline
const T & Vector<T>::operator()(Index i) const
{
  return data(i);
}

template<class T> inline
Vector<T> & Vector<T>::operator*=(const T & c)
{
  data *= c;
  return *this;
}

template<class T> inline
Vector<T> & Vector<T>::operator/=(const T & c)
{
  data /= c;
  return *this;
}

template<class T> inline
Vector<T> & Vector<T>::operator+=(const Vector & other)
{
  ASSERT( data.size() == other.size() );
  data += other.data;
  return *this;
}

template<class T> inline
Vector<T> & Vector<T>::operator-=(const Vector & other)
{
  ASSERT( data.size() == other.size() );
  data -= other.data;
  return *this;
}
