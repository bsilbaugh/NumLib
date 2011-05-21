/*! \file Vector-inl.h
 */

template<class T>
Vector<T>::Vector(Size n_):
	n(n_),
	data(NULL)
{
	data = new T[n];
}

template<class T>
Vector<T>::Vector(const Vector & other)
{
	n = other.n;
	data = new T[n];
	for(Index i=0; i<n; ++i)
		data[i] = other.data[i];
}

template<class T>
Vector<T>::~Vector()
{
	delete[] data;
}

template<class T>
Vector<T> & Vector<T>::operator=(const Vector & other)
{
  if(&other==this) return *this;

  delete[] data;
  n = other.n;
  data = new T[n];
  for(Index i=0; i<n; ++i)
	  data[i] = other.data[i];
  return *this;
}

template<class T>
void Vector<T>::zero()
{
  T z(0);
  for(Index i=0; i<n; ++i)
  	data[i] = z;
}

template<class T> inline
Size Vector<T>::size() const
{
  return n;
}

template<class T>
void Vector<T>::resize(Size n_)
{
	delete[] data;
	n = n_;
	data = new T[n];
}

template<class T> inline
T & Vector<T>::operator()(Index i)
{
  return data[i];
}

template<class T> inline
const T & Vector<T>::operator()(Index i) const
{
  return data[i];
}

template<class T> inline
Vector<T> & Vector<T>::operator*=(const T & c)
{
	for(Index i=0; i<n; ++i)
  		data[i] *= c;
  	return *this;
}

template<class T> inline
Vector<T> & Vector<T>::operator/=(const T & c)
{
	ASSERT( !is_zero(c) );
	for(Index i=0; i<n; ++i)
  		data[i] /= c;
  	return *this;
}

template<class T> inline
Vector<T> & Vector<T>::operator+=(const Vector & other)
{
  ASSERT( data.size() == other.size() );
  for(Index i=0; i<n; ++i)
  	data[i] += other.data[i];
  return *this;
}

template<class T> inline
Vector<T> & Vector<T>::operator-=(const Vector & other)
{
  	ASSERT( data.size() == other.size() );
	for(Index i=0; i<n; ++i)
  		data[i] -= other.data[i];
  	return *this;
}
