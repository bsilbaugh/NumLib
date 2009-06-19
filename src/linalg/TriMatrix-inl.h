
template<class T>
TriMatrix<T>::TriMatrix(Size n_):
  n(n_),zero(0),lowerBand(n),diagBand(n),upperBand(n)
{
  lowerBand(0) = zero;
  upperBand(n-1) = zero;
}

template<class T>
TriMatrix<T>::TriMatrix(const TriMatrix & other):
  n(other.n), 
  zero(0),
  lowerBand(other.lowerBand), 
  diagBand(other.diagBand), 
  upperBand(other.upperBand)
{
}

template<class T>
TriMatrix<T>::~TriMatrix()
{
  /* nothing to delete */
}

template<class T>
TriMatrix<T> & TriMatrix<T>::operator=(const TriMatrix & other)
{
  if(&other != this)
  {
	n = other.n;
	lowerBand = other.lowerBand;
	diagBand = other.diagBand;
	upperBand = other.upperBand;
  }
  return *this;
}

template<class T> inline
T & TriMatrix<T>::lower(Index k)
{
  ASSERT( k < n );
  return lowerBand(k);
}

template<class T> inline
T & TriMatrix<T>::diag(Index k)
{
  ASSERT( k < n );
  return diagBand(k);
}

template<class T> inline
T & TriMatrix<T>::upper(Index k)
{
  ASSERT( k < n );
  return upperBand(k);
}

template<class T> inline
const T & TriMatrix<T>::lower(Index k) const
{
  ASSERT( k < n );
  return lowerBand(k);
}

template<class T> inline
const T & TriMatrix<T>::diag(Index k) const
{
  ASSERT( k < n );
  return diagBand(k);
}

template<class T> inline
const T & TriMatrix<T>::upper(Index k) const
{
  ASSERT( k < n );
  return upperBand(k);
}

template<class T> inline
Size TriMatrix<T>::size1() const
{
  return n;
}

template<class T> inline
Size TriMatrix<T>::size2() const
{
  return size1();
}

template<class T> inline
const T & TriMatrix<T>::operator()(Index i, Index j) const
{
  if (j == i)
	return diag(i);
  else if(j == i-1)
	return lower(i);
  else if(j == i+1) 
	return upper(i);
  else
	return zero;
}

template<class T>
TriMatrix<T> & TriMatrix<T>::operator*=(const T & c)
{
  lowerBand *= c;
  diagBand *= c;
  upperBand *= c;
  return *this;
}

template<class T>
TriMatrix<T> & TriMatrix<T>::operator/=(const T & c)
{
  ASSERT(c > zero);
  lowerBand /= c;
  diagBand /= c;
  upperBand /= c;
  return *this;
}

template<class T>
TriMatrix<T> & TriMatrix<T>::operator+=(const TriMatrix & other)
{
  lowerBand += other.lowerBand;
  diagBand  += other.diagBand;
  upperBand += other.upperBand;
  return *this;
}

template<class T>
TriMatrix<T> & TriMatrix<T>::operator-=(const TriMatrix & other)
{
  lowerBand -= other.lowerBand;
  diagBand  -= other.diagBand;
  upperBand -= other.upperBand;
  return *this;
}

