/*! \file SquareMatrix.h
 *  \brief SquareMatrix class definition and implementation
 */

#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include "Vector.h"

namespace numlib{ namespace linalg{

//! Model of a square matrix
/*!
 *	This should be used for dense matricies, or small matricies in which
 *	performance is not a concern.
 *
 *	Template parameter T may be any model of a scalar (i.e. all of the
 *	standard mathematical operations for float/double have been defined
 *	for T). For example, T could be a model of a complex number.
 *
 *	All the basic matrix-matrix and matrix-vector operations are defined 
 *	for this class. Additional operators will be defined in future on an
 *	as needed basis.
 */
template<class T>
class SquareMatrix
{
public:

	SquareMatrix(Size dim_=0);

	SquareMatrix(const SquareMatrix& other);

	~SquareMatrix();

	SquareMatrix& operator=(const SquareMatrix& other);

	/*------------------------------------------------------------------------*/
	/*                                                         Element Access */

	//! Returns the number of rows (columns) of the matrix
	Size size() const;

	//! Returns mutable reference to matrix element i,j
	T& operator()(Index i, Index j);

	//! Returns immutable reference to matrix element i,j
	const T& operator()(Index i, Index j) const;

	/*------------------------------------------------------------------------*/
	/*                                                     In-place Operators */

	SquareMatrix& zero();

	SquareMatrix& operator*=(const T& c);

	SquareMatrix& operator/=(const T& c);

	SquareMatrix& operator+=(const SquareMatrix& other);

	SquareMatrix& operator-=(const SquareMatrix& other);

private:

	//! Number of rows (columns)
	Size dim;

	//! Total number of elements
	Size n;

	//! Matrix elements (column major order)
	T* data;

};

/*----------------------------------------------------------------------------*/

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

#endif
