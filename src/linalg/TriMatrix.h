/*! \file TriMatrix.h
 */

#ifndef TRIMATRIX_H
#define TRIMATRIX_H

#include "../array/Array1D.h"
#include "Vector.h"

namespace numlib{ namespace linalg{

//! Model of a tri-diagonal matrix
/*
 *  
 *         [d_0, u_0, 0, ........................,  0     ]
 *         [l_1, d_1, u_1, 0, ...................,  0     ]
 *         [ 0 , l_2, d_2, u_2, 0, ..............,  0     ]
 *   [A] = [                                              ]
 *         [ 0, ..., 0, l_{n-2}, d_{n-2}, u_{n-1},  0     ]
 *         [ 0, ......., 0     , l_{n-1}, d_{n-1}, u_{n-1}]
 */
template<class T>
class TriMatrix
{
public:

	 TriMatrix(Size n_=0);

	 TriMatrix(const TriMatrix & other);

	 ~TriMatrix();

	 TriMatrix & operator=(const TriMatrix & other);

	 /* Tri-diagnoal container interface */

	 //! Sets/returns kth row element in lower band
	 T & lower(Index k);

	 //! Sets/returns kth row element in diagonal
	 T & diag(Index k);

	 //! Sets/returns kth row element in upper band
	 T & upper(Index k);

	 //! Returns kth row element in lower band
	 const T & lower(Index k) const;

	 //! Returns kth row element in diagonal
	 const T & diag(Index k) const;

	 //! Returns kth row element in upper band
	 const T & upper(Index k) const;

	 //! Resizes array to n x n; contents not preserved
	 void resize(Size n_);

	 /* Generic matrix container interface */

	 Size size1() const;

	 Size size2() const;

	 const T & operator()(Index i, Index j) const;

	 /* In-place arithmetic operators */

	 TriMatrix & operator*=(const T & c);

	 TriMatrix & operator/=(const T & c);

	 TriMatrix & operator+=(const TriMatrix & other);

	 TriMatrix & operator-=(const TriMatrix & other);

	 /* Friend operators */

	 template<class M> friend
	 Vector<M> prod(const TriMatrix<M> & a, const Vector<M> & u);

private:

	 typedef array::Array1D<T> Array;

	 //! Number of rows and columns
	 Size n;

	 //! Zero element
	 T zero;

	 //! Lower band
	 Array lowerBand;

	 //! Diagonal
	 Array diagBand;

	 //! Upper band
	 Array upperBand;

};

#include "TriMatrix-inl.h"

}}//::numlib::linalg

#endif
