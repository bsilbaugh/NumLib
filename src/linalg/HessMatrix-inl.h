/*! \file HessMatrix.h
 */

template<class T>
HessMatrix<T>::HessMatrix(Size m_):
	 m(m_),
	 columns(NULL),
	 zero(0)
{
	columns = new Vector<T>[m];
	for(Index j=0; j<m-1; ++j)
		columns[j].resize(j+2);
	columns[m-1].resize(m);
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
	 if(&other != this) copy(other);
	 return *this;
}

template<class T> inline
Size HessMatrix<T>::size1() const
{
	 return n;
}

template<class T> inline
Size HessMatrix<T>::size2() const
{
	 return m;
}

template<class T> inline
T & HessMatrix<T>::operator()(Index i, Index j)
{
	ASSERT( i < n );
	ASSERT( j < m );

	if(i < j+2)
		return columns[j](i);

	return zero;
}

template<class T> inline
const T & HessMatrix<T>::operator()(Index i, Index j) const
{
	ASSERT( i < n );
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

template<class T>
void HessMatrix<T>::copy(const HessMatrix & other)
{
	 delete[] columns;

	 n = other.n;
	 m = other.m;
	 columns = new Vector<T>[m];
	 for(Index i=0; i<m; ++i)
		  columns[i] = other.columns[i];
}
