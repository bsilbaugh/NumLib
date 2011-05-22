/*! \file SquareMatrix.h
 *  \brief SquareMatrix class definition
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

}}//::numlib::linalg

#include "SquareMatrix-inl.h"

#endif
