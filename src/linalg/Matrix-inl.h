/*! \file Matrix-inl.h
 */

namespace numlib{ namespace linalg{

template<class T>
Matrix<T>::Matrix():
	n(0),
	m(0),
	data(0)
{
}

template<class T>
Matrix<T>::Matrix(Size nrows, Size ncols):
	n(nrows),
	m(ncols),
	data(0)
{
	data = new T[n*m];
}

template<class T>
Matrix<T>::Matrix(const Matrix& other):
	n(other.n),
	m(other.m)
{
	data = new T[n*m];
	for(Index i=0; i<n*m; ++i)
		data[i] = other.data[i];
}

template<class T>
Matrix<T>::~Matrix()
{
	delete[] data;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other)
{
	if(&other==this) return *this;

	delete[] data;

	n = other.n;
	m = other.m;
	data = new T[n*m];
	for(Index k=0; k<n*m; ++k)
		data[k] = other.data[k];

	return *this;
}

template<class T>
const Size Matrix<T>::size1() const {return n;}

template<class T>
const Size Matrix<T>::size2() const {return m;}

template<class T>
void Matrix<T>::resize(const Size nrows, const Size ncols)
{
	delete[] data;
	n = nrows;
	m = ncols;
	data = new T[n*m];
}

template<class T>
T& Matrix<T>::operator()(Index i, Index j)
{
	return data[i + j*n];
}

template<class T>
const T& Matrix<T>::operator()(Index i, Index j) const
{
	return data[i + j*n];
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const T& c)
{
	for(Index k=0; k<n*m; ++k)
		data[k] *= c;
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator/=(const T& c)
{
	for(Index k=0; k<n*m; ++k)
		data[k] /= c;
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& other)
{
	ASSERT( other.n == n );
	ASSERT( other.m == m );
	for(Index k=0; k<n*m; ++k)
		data[k] += other.data[k];
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& other)
{
	ASSERT( other.n == n );
	ASSERT( other.m == m );
	for(Index k=0; k<n*m; ++k)
		data[k] -= other.data[k];
	return *this;
}

}}//::numlib::linalg
