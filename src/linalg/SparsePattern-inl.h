/*! \file SparsePattern-inl.h
 */

template<class KeyType> inline
SparsePattern<KeyType>::SparsePattern(Size nn_)
{
  nn = nn_;
  keys = new KeyType[nn];
}

template<class KeyType> inline
SparsePattern<KeyType>::SparsePattern(const SparsePattern & other)
{
  copy(other);
}

template<class KeyType>
SparsePattern<KeyType>::~SparsePattern()
{
  DEBUG_PRINT( "SparsePattern destructor called" );
  delete[] keys;
}

template<class KeyType> inline
SparsePattern<KeyType> & SparsePattern<Keytype>::operator=(const SparsePattern & other)
{
  if(*other != this)
	copy(other);
  return *this;
}

template<class KeyType> inline
Size SparsePattern<KeyType>::size()
{
  return nn;
}

template<class KeyType> inline
KeyType & SparsePattern<KeyType>::operator[](Index k)
{
  ASSERT( k < nn );
  return keys[k];
}

template<class KeyType> inline
const KeyType & SparsePattern<KeyType>::operator[](Index k) const
{
  ASSERT( k < nn );
  return keys[k];
}

template<class KeyType> inline
void SparsePattern<KeyType>::copy(const SparsePattern & other)
{
 delete[] keys;
  
  nn = other.nn;

  keys = new KeyType[nn];
  for(Index i=0; i<nn; ++i)
	keys[i] = other.keys[i];
}
