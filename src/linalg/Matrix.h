/*! \file Matrix.h
 *  \brief Matrix class definition
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "../base/numlib-config.h"

namespace numlib{ namespace linalg{

template<class T>
class Matrix
{
public:

	Matrix();

	Matrix(Size nrows, Size ncols);

	Matrix(const Matrix& other);

	~Matrix();

	Matrix& operator=(const Matrix& other);

	/*------------------------------------------------------------------------*/
	/*                                                            MATRIX SIZE */

	//! Returns the first matrix dimension (number of rows)
	const Size size1() const;

	//! Returns the second matrix dimension (number of rows)
	const Size size2() const;

	//! Resizes matrix to nrows by ncols
	/*!
	 *	This does not preserve any submatrix that results by
	 *	adding/removing rows or columns to the existing matrix.
	 *	This function is provided to support default construction
	 *	of a zero dimensional matrix, which is then effectively
	 *	redefined as a nrows by ncols matrix once nrows and ncols
	 *	is known (possibly determined later in the program from 
	 *	user inputs or completion of another subprogram).
	 */
	void resize(const Size nrows, const Size ncols);

	/*------------------------------------------------------------------------*/
	/*                                                         ELEMENT ACCESS */

	//! Returns mutable reference to matrix element i,j
	T& operator()(Index i, Index j);

	//! Returns immutable reference to matrix element i,j
	const T& operator()(Index i, Index j) const;

	/*------------------------------------------------------------------------*/
	/*                                                     IN-PLACE OPERATORS */

	Matrix& operator*=(const T& c);

	Matrix& operator/=(const T& c);

	Matrix& operator+=(const Matrix& other);

	Matrix& operator-=(const Matrix& other);

private:

	//! Number of rows
	Size n;
	
	//! Number of columns
	Size m;

	//! Matrix elements (column major order)
	T* data;
};

}}//::numlib::linalg

#include "Matrix-inl.h"

#endif
