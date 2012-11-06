/*! \file HessMatrix.h
 */

#ifndef HESSMATRIX_H
#define HESSMATRIX_H

#include "../base/numlib-config.h"
#include "../base/debug_tools.h"
#include "Vector.h"

namespace numlib{ namespace linalg{

// Forward declarations
template<class T> class ExtHessMatrix;

//! Hessenberg Matrix
/*! 
 *  Model of an (upper) Hessenberg matrix, which provides a more efficient
 *  storage scheme and matrix-vector operations than a generalized sparse
 *  matrix (or dense matrix). The data structure assumes an upper Hessenberg
 *  matrix (i.e. all zeros below the first subdiagonal); a lower Hessenberg
 *  may be modeled by imposing a transpose operation.
 *
 */
template<class T>
class HessMatrix
{
public:

	 //! Constructs a Hessenberg matrix of dim (m,m) or (m+1,m) if extended
	 HessMatrix(Size m_=0);

	 //! Copy constructor (deep copy)
	 HessMatrix(const HessMatrix & other);

	 //! Constructs an m x m Hessenberg from and m+1 x m Hessenberg
	 explicit HessMatrix(const ExtHessMatrix<T> & other);

	 //! Destructor
	 ~HessMatrix();

	 //! Assignment (deep copy)
	 HessMatrix & operator=(const HessMatrix & other);

	/*------------------------------------------------------------------------*/
	/*                                                        Array interface */

	 //! Returns number of rows
	 Size size1() const;

	 //! Returns number of columns
	 Size size2() const;

	 //! Sets/returns (i,j) element
	 /*!
	  *  WARNING: Assignment to a element in the assumed zero region is undefined. 
      *  An error of this nature is difficult to detect since it cannot
	  *  be known (locally) if an assignment is being made. 
      *
      *  When compiled in debug mode, checks will be performed to ensure that
      *  index values are sane. Otherwise, you're on your own.
      *
      *  \todo Fix this?
	  */
	 T & operator()(Index i, Index j);

	 //! Return the (i,j) element
	 /*!
	  *  If the (i,j) is in the assumed zero region of the matrix, a zero element
	  *  will be returned. Assignment to a element in the assumed zero region is
	  *  undefined. An error of this nature is difficult to detect since it cannot
	  *  be known (locally) if an assignment is being made. \todo Fix this?
	  */
	 const T & operator()(Index i, Index j) const;

	/*------------------------------------------------------------------------*/
	/*                                                     In-place operators */

	 /* In-place arithmetic operations */

	 HessMatrix & operator*=(const T & c);

	 HessMatrix & operator/=(const T & c);

	 HessMatrix & operator+=(const HessMatrix & other);

	 HessMatrix & operator-=(const HessMatrix & other);

private:

	 //! Number of columns
	 Size m;

	 //! Matrix column vectors
	 Vector<T>* columns;

	 //! Zero element
	 const T zero;

};

/*----------------------------------------------------------------------------*/
/*                                                     IMPLEMENTATION DETAILS */

template<class T>
HessMatrix<T>::HessMatrix(Size m_):
	 m(m_),
	 columns(NULL),
	 zero(0)
{
	if(m > 0)
	{
		columns = new Vector<T>[m];
		for(Index j=0; j<m-1; ++j)
			columns[j].resize(j+2);
		columns[m-1].resize(m);
	}
}

template<class T>
HessMatrix<T>::HessMatrix(const HessMatrix & other):
	 m(0),columns(0),zero(0)
{
	 m = other.m;
	 columns = new Vector<T>[m];
	 for(Index j=0; j<m; ++j)
		 columns[j] = other.columns[j];
}

template<class T>
HessMatrix<T>::HessMatrix(const ExtHessMatrix<T> & other):
	 m(0),columns(NULL),zero(0)
{
	m = other.m;
	columns = new Vector<T>[m];
	for(Index j=0; j<m-1; ++j)
		columns[j] = other.columns[j];
	for(Index i=0; i<m; ++i)
		columns[m-1](i) = other.columns[m-1](i);
}

template<class T>
HessMatrix<T>::~HessMatrix()
{
	 delete[] columns;
}

template<class T>
HessMatrix<T> & HessMatrix<T>::operator=(const HessMatrix & other)
{
    if(&other==this) return *this;
    m = other.m;
    columns = new Vector<T>[m];
    for(Index j=0; j<m-1; ++j)
        for(Index i=0; i<j+2; ++i)
            columns[j] = other.columns[j];
        for(Index i=0; i<m; ++i)
            columns[m-1] = other.columns[m-1];
    return *this;
}

template<class T> inline
Size HessMatrix<T>::size1() const
{
	 return m;
}

template<class T> inline
Size HessMatrix<T>::size2() const
{
	 return m;
}

template<class T> inline
T & HessMatrix<T>::operator()(Index i, Index j)
{
    ASSERT( i < m   );
    ASSERT( j < m   );
    ASSERT( i < j+2 );
   	return columns[j](i);

    /********************************************************** 
     * we can't return a zero for i >= j+2 here because
     * we don't know if the user is getting or setting values.
     * So, we throw an exception instead (when in debug mode).
     *********************************************************/
}

template<class T> inline
const T & HessMatrix<T>::operator()(Index i, Index j) const
{
    ASSERT( i < m );
    ASSERT( j < m );
    if(i < j+2)
    	return columns[j](i);
    return zero;
}

template<class T>
HessMatrix<T> & HessMatrix<T>::operator*=(const T & c)
{
	 for(Index j=0; j<m; ++j)
		  columns[j] *= c;
}

template<class T>
HessMatrix<T> & HessMatrix<T>::operator/=(const T & c)
{
	 for(Index j=0; j<m; ++j)
		  columns[j] /= c;
}

template<class T>
HessMatrix<T> & HessMatrix<T>::operator+=(const HessMatrix & other)
{
	 for(Index j=0; j<m; ++j)
		  columns[j] += other.columns[j];
}

template<class T>
HessMatrix<T> & HessMatrix<T>::operator-=(const HessMatrix & other)
{
	 for(Index j=0; j<m; ++j)
		  columns[j] -= other.columns[j];
}

}}//::numlib::linalg

#endif
