/*! \file HessMatrix.h
 */

#ifndef HESSMATRIX_H
#define HESSMATRIX_H

namespace numlib{ namespace linalg{

//! Hessenberg Matrix
/*! 
 *  Model of an (upper) Hessenberg matrix, which provides a more efficient
 *  storage scheme and matrix-vector operations than a generalized sparse
 *  matrix (or dense matrix). The data structure assumes an upper Hessenberg
 *  matrix (i.e. all zeros below the first subdiagonal); a lower Hessenberg
 *  may be modeled by imposing a transpose operation.
 *
 *  The notion of an "extended" Hessenberg matrix arises in Krylov methods
 *  for solving linear systems. The extended Hessenberg matrix is equivolent
 *  to a regular Hessenberg matrix with an additional, m+1, row. The elements
 *  of the m+1 row are all zero except for the last element. Instead of modeling
 *  the extended Hessenberg with a different type, this class models both forms
 *  by allowing for a variable number of rows (i.e. either m or m+1, where m
 *  is the number of columns). Modeling regular and extended Hessenberg forms
 *  with distinct types would introduce significant implementation redundancy.
 *  The penalty is the additional bookeeping required to ensure
 *  consistent usage when both Hessenberg forms co-exist; this penalty, however,
 *  is no worse than ensuring proper matrix/vector dimensions when dealing with
 *  dense matrix/vector models.
 */
template<class T>
class HessMatrix
{
public:

	 //! Constructs a Hessenberg matrix of dim (m,m) or (m+1,m) if extended
	 HessMatrix(Size m_, bool extended=false);

	 //! Copy constructor (deep copy)
	 HessMatrix(const HessMatrix & other);

	 //! Constructs an m x m Hessenberg from and m+1 x m Hessenberg
	 HessMatrix(const HessMatrix & other, bool extended);

	 //! Destructor
	 ~HessMatrix();

	 //! Assignment (deep copy)
	 HessMatrix & operator=(const HessMatrix & other);

	 //! Returns number of rows
	 Size size1() const;

	 //! Returns number of columns
	 Size size2() const;

	 //! Sets/returns (i,j) element
	 /*!
	  *  If the (i,j) is in the assumed zero region of the matrix, a zero element
	  *  will be returned. Assignment to a element in the assumed zero region is
	  *  undefined. An error of this nature is difficult to detect since it cannot
	  *  be known (locally) if an assignment is being made. \todo Fix this?
	  */
	 T & operator()(Index i, Index j);

	 //! Return the (i,j) element
	 const T & operator()(Index i, Index j) const;

	 /* In-place arithmetic operations */

	 HessMatrix & operator*=(const T & c);

	 HessMatrix & operator/=(const T & c);

	 HessMatrix & operator+=(const HessMatrix & other);

	 HessMatrix & operator-=(const HessMatrix & other);

private:

	 //! Nubmer of rows
	 Size n;

	 //! Number of columns
	 Size m;

	 //! Matrix column vectors
	 Vector<T>* columns;

	 //! Zero element
	 T zero;

	 //! Copy function
	 void copy(const HessMatrix & other);

};

#include "HessMatrix-inl.h"

}}//::numlib::linalg

#endif
