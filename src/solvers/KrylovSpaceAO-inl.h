/*! \file KrylovSpaceAO.h
 */

template<class T, class L>
KrylovSpaceAO<T,L>::KrylovSpaceAO(Size n_, Size maxSpaceDim):
  n(n_),m(0),mmax(maxSpaceDim),basis(0),hess(mmax,true)
{
  basis = new VecType[mmax];
  for(Index i=0; i<mmax; ++i)
	   basis[i].resize(n);
};

template<class T, class L>
void KrylovSpaceAO<T,L>::buildSpace(const L & linO, const VecType & r, const T & tol)
{

  // Reset Krylov space dimension...

  m = 0;

  // Seed Krylov space using normalized residual vector...

  VecType v(r);
  T beta = norm2(v);
  if(beta < tol) return; /* "happy breakdown" */
  v /= beta;


  // Construct orthonomal Krylov basis using modified Grahm-Schmit ...

  for(Index j=0; j<mmax; ++j)
  {
	
	// Update subspace basis set...

	++m;
	basis[j] = v;

	// Compute j+1 Krylov basis v_{j+1} = A v_{j} ...

	v = prod(linO, v);

	// Project v onto existing orthonormal basis...

	for(Index i=0; i<m; ++i)
	  hess(i,j) = prod(v,basis[i]);

	// Reduce v to it's ortho component...

	for(Index i=0; i<m; ++i)
	  v -= hess(i,j)*basis[i];

	// Normalize v...

	T h = norm2(v);
	hess(j+1,j) = h;
	if(h < tol) return; /* happy breakdown */
	v /= h;

  }

}

template<class T, class L>
void KrylovSpaceAO<T,L>::projA(HessType & h)
{
  for(Index i=0; i<m+1; ++i)
	for(Index j=0; j<m; ++j)
	  h(i,j) = hess(i,j);
}

template<class T, class L>
void KrylovSpaceAO<T,L>::map(const VecType & y, VecType & z)
{
  z.zero();
  for(Index i=0; i<m; ++i)
	z += basis[i]*y(i);
}
