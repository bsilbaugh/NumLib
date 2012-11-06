/*! \file ExtHessMatrix.h */

#ifndef EXT_HESS_MATRIX_H
#define EXT_HESS_MATRIX_H

#include "../linalg/Vector.h"

namespace numlib{ namespace linalg{

// Forward declaration
template<class T> class HessMatrix;

//! Extended Hessenberg Matrix
/*! 
 *  Model of an (upper) Extended Hessenberg matrix, which provides a more efficient
 *  storage scheme and matrix-vector operations than a generalized sparse
 *  matrix (or dense matrix). The data structure assumes an upper Hessenberg
 *  matrix (i.e. all zeros below the first subdiagonal).
 *
 *  The notion of an "extended" Hessenberg matrix arises in Krylov methods
 *  for solving linear systems. The extended Hessenberg matrix is equivolent
 *  to a regular Hessenberg matrix with an additional, m+1, row. The elements
 *  of the m+1 row are all zero except for the last element. 
 */
template<class T>
class ExtHessMatrix
{
public:

	//! Constructs an extended hessinburg matrix of dimension (m+1) X m
	ExtHessMatrix(Size m_=0);

	//! (deep) copy constructor
	ExtHessMatrix(const ExtHessMatrix& other);

	//! Constructs extended hessinburg (m+1 X m) from hessinburg (m X m)
	explicit ExtHessMatrix(const HessMatrix<T>& other);

	//! Destructor
	~ExtHessMatrix();

	/*------------------------------------------------------------------------*/
	/*                                                        Array interface */

	//! Returns the number of rows
	const Size size1() const;

	//! Returns the number of columns
	const Size size2() const;

	//! Sets/returns (i,j) element
    /*!
     *  If the (i,j) is in the assumed zero region of the matrix, a zero element
	 *  will be returned. Assignment to a element in the assumed zero region is
	 *  undefined. An error of this nature is difficult to detect since it cannot
	 *  be known (locally) if an assignment is being made. \todo Fix this?
	 */
	T& operator()(Index i, Index j) {return element(i,j);}

	//! Returns the (i,j) element
	const T& operator()(Index i, Index j) const {return element(i,j);}

	/*------------------------------------------------------------------------*/
	/*                                                     In-place operators */

	ExtHessMatrix & operator*=(const T & c);
	
	ExtHessMatrix & operator/=(const T & c);
	
	ExtHessMatrix & operator+=(const ExtHessMatrix & other);
	
	ExtHessMatrix & operator-=(const ExtHessMatrix & other);

private:

	// Number of columns
	Size m;

	// Matrix column vectors
	Vector<T>* columns;

	// Zero element
	T zero;

	// A helper function for setting/getting elements...
	T& element(Index i, Index j)
	{
		ASSERT( i < m+1 );
		ASSERT( j < m );
		if(i < j + 2) 
			return columns[j](i);
		return zero;
	}

};

/*---------------------------------------------------------------------------*/
/*                                                            IMPLEMENTATION */

template<class T>
ExtHessMatrix<T>::ExtHessMatrix(Size m_):
	m(m_),
	columns(NULL),
	zero(0)
{
	columns = new Vector<T>[m];
	for(Index i=0; i<m; ++i)
		columns[i].resize(i+2);
}

template<class T>
ExtHessMatrix<T>::ExtHessMatrix(const ExtHessMatrix<T>& other):
	m(0),columns(NULL),zero(0)
{
	m = other.m;
	columns = new Vector<T>[m];
	for(Index i=0; i<m; ++i)
		columns[i] = other.column[i];

}

template<class T>
ExtHessMatrix<T>::ExtHessMatrix(const HessMatrix<T>& other):
	m(0),columns(NULL),zero(0)
{
	// Set number of columns...
	m = other.m;

	// Allocate column vectors...

	columns = new Vector<T>[m];

	// copy all columns vectors but the last...
	for(Index i=0; i<m-1; ++i)
		columns[i] = other.columns[i];

	// Now copy the last column vector into the "extended" column vector...
	columns[m-1].resize(m+1);
	for(Index i=0; i<m+1; ++i)
		columns[m-1](i) = other.columns[m-1](i);
	columns[m-1](m) = 0;
}

template<class T>
ExtHessMatrix<T>::~ExtHessMatrix<T>()
{
	delete[] columns;
}

template<class T>
const Size ExtHessMatrix<T>::size1() const
{
	return m+1;
}

template<class T>
const Size ExtHessMatrix<T>::size2() const
{
	return m;
}

template<class T>
ExtHessMatrix<T>& ExtHessMatrix<T>::operator*=(const T& c)
{
	for(Index i=0; i<m; ++i)
		columns[i] *= c;
}

template<class T>
ExtHessMatrix<T>& ExtHessMatrix<T>::operator/=(const T& c)
{
	for(Index i=0; i<m; ++i)
		columns[i] /= c;
}

template<class T>
ExtHessMatrix<T>& ExtHessMatrix<T>::operator+=(const ExtHessMatrix& other)
{
	for(Index i=0; i<m; ++i)
		columns[i] += other.columns[i];
}

template<class T>
ExtHessMatrix<T>& ExtHessMatrix<T>::operator-=(const ExtHessMatrix& other)
{
	for(Index i=0; i<m; ++i)
		columns[i] -= other.columns[i];
}

}}//::numlib::linalg

#endif
