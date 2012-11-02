/*! \file ExtHessMatrix.h */

namespace numlib{ namespace linalg{

template<class T>
ExtHessMatrix<T>::ExtHessMatrix(Size m_):
	m(m_)
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
	columns[m-1].resize(n);
	for(Index i=0; i<m; ++i)
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
