/*! \file PointerArray-inl.h
 *  \brief Implimentation of inline member functions for PointerArray
 */

namespace numlib{ namespace array{

template<class T>
PointerArray<T>::PointerArray(Size n_):n(n_)
{
	data = new T*[n];
	for(Index i=0; i<n; i++)
		data[i] = 0;
}

template<class T>
PointerArray<T>::PointerArray(const PointerArray & other)
{
	copy(other);
}

template<class T>
PointerArray<T>::~PointerArray()
{
	delete[] data;
}

template<class T>
PointerArray<T> & PointerArray<T>::operator=(const PointerArray & other)
{
	if(&other != this)
	{
		delete[] data;
		copy(other);
	}
	return *this;
}

template<class T>
Size PointerArray<T>::size() const
{
	return n;
}

template<class T>
void PointerArray<T>::resize(Size n_)
{
	// if n_ is strickly greater than or less then n, then resize
	// otherwise assume n_ == n and do nothing.
	
	if(n_ > n)
		expand(n_);
	else if(n_ < n)
		truncate(n_);
}

template<class T>
void PointerArray<T>::clear()
{
	T** ptr;
	for(ptr = data; ptr != data+n; ptr++)
	{
		delete *ptr;
		*ptr = 0;
	}
}

template<class T>
T*& PointerArray<T>::operator[](Index i)
{
	return data[i];
}

template<class T>
const T* PointerArray<T>::operator[](Index i) const
{
	return data[i];
}


// Private functions

template<class T>
void PointerArray<T>::copy(const PointerArray & other)
{
	n = other.n;
	data = new T*[n];
	for(Index i=0; i<n; i++)
		data[i] = other.data[i];
}

template<class T>
void PointerArray<T>::expand(Size n_)
{
	T** data_new;
	Index i;
	data_new = new T*[n_];
	for(i=0; i<n; i++)
		data_new[i] = data[i];
	for(i=n; i<n_; i++)
		data_new[i] = 0;
	delete[] data;
	n = n_;
	data = data_new;
}

template<class T>
void PointerArray<T>::truncate(Size n_)
{
	T** data_new;
	Index i;
	data_new = new T*[n_];
	for(i=0; i<n_; i++)
		data_new[i] = data[i];
	delete[] data;
	n = n_;
	data = data_new;
}

}} //::numlib::array
