/*! \file SparseVector-inl.h
 */

template<class T>
SparseVector<T>::SparseVector(Size n_, Size nn):
  n(n_),kin(0),sp(nn),val(sp.size()),zero(0)
{
  // Initialize index values in sparsity pattern to zero...

  sp = 0;

  /* leave val to default initialization */

}

template<class T>
SparseVector<T>::SparseVector(const SparseVector & other)
{
  copy(other);
}

template<class T>
SparseVector<T>::~SparseVector()
{
  /* nothing to delete */
}

template<class T>
SparseVector<T> & SparseVector<T>::operator=(const SparseVector & other)
{
  if(*other!=this) copy(other);
  return *this;
}

template<class T> inline
Size SparseVector<T>::size()
{
  return n;
}

template<class T>
const T & SparseVector<T>::set(Index i, const T & value)
{

  ASSERT( kin < sp.size() );

  bool insert_new = true;

  /* Check if element previously initialized - if true then overwrite value */

  for(Index k=0; k<kin; ++k)
  {
	if(i == sp(k))
	{
	  val(k) = value;
	  insert_new = false;
	  break;
	}
  }

  if(insert_new)
  {
	// Initialize new element...

	sp(kin) = i;
	val(kin) = value;
	++kin;
  }

}

template<class T>
const T & SparseVector<T>::operator()(Index i) const
{
  for(Index k=0; k<sp.size(); ++k)
	if(i == sp(k)) return val(k);
  return zero;
}

template<class T> inline
SparseVector<T> & SparseVector<T>::operator*=(const T & c);
{
  val *= c;
}

template<class T> inline
SparseVector<T> & SparseVector<T>::operator/=(const T & c);
{
  val /= c;
}
