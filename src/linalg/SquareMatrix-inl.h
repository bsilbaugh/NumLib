/*! \file SquareMatrix.cpp
 *  \brief SquareMatrix class implementation
 */

#include "SquareMatrix.h"

namespace numlib{ namespace linalg{

template<class T>
SquareMatrix<T>::SquareMatrix(Size dim_):
	dim(dim_),
	n(dim*dim),
	data(NULL)
{
	data = new T[n];
}

template<class T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix& other)
{
	dim = other.dim;
	n = other.n;
	data = new T[n];
	for(Index i=0; i<n; ++i)
		data[i] = other.data[i];
}

template<class T>
SquareMatrix<T>::~SquareMatrix()
{
	delete[] data;
}

template<class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix& other)
{
	if(&other==this) return *this;
	delete[] data;
	dim = other.dim;
	n = other.n;
	data = new T[n];
	for(Index i=0; i<n; ++i)
		data[i] = other.data[i];
	return *this;
}

template<class T> inline
Size SquareMatrix<T>::size() const
{
	return dim;
}

template<class T> inline
T& SquareMatrix<T>::operator()(Index i, Index j)
{
	ASSERT( i < dim );
	ASSERT( j < dim );
	return data[i+j*dim];
}

template<class T> inline
const T& SquareMatrix<T>::operator()(Index i, Index j) const
{
	ASSERT( i < dim );
	ASSERT( j < dim );
	return data[i+j*dim];
}

template<class T>
SquareMatrix<T>& SquareMatrix<T>::zero()
{
	for(Index i=0; i<n; ++i)
		data[i] = 0.0;
}

template<class T>
SquareMatrix<T>& SquareMatrix<T>::operator*=(const T& c)
{
	for(Index i=0; i<n; ++i)
		data[i] *= c;
	return *this;
}

template<class T>
SquareMatrix<T>& SquareMatrix<T>::operator/=(const T& c)
{
	for(Index i=0; i<n; ++i)
		data[i] /= c;
	return *this;
}

template<class T>
SquareMatrix<T>& SquareMatrix<T>::operator+=(const SquareMatrix& other)
{
	ASSERT(other.n == n);
	for(Index i=0; i<n; ++i)
		data[i] += other.data[i];
	return *this;
}

template<class T>
SquareMatrix<T>& SquareMatrix<T>::operator-=(const SquareMatrix& other)
{
	ASSERT(other.n == n);
	for(Index i=0; i<n; ++i)
		data[i] -= other.data[i];
	return *this;
}

}}//::numlib::linalg
