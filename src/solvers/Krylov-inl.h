/*! \file Krylov-inl.h
 */

template<class T, class L, class K, class P>
Krylov<T,L,K,P>::Krylov(Size n_, Size mmax_):
  n(n_),m(0),mmax(mmax_),krylovSpace(n_,mmax_)
{
  ASSERT(mmax <= n);
}

template<class T, class L, class K, class P>
T Krylov<T,L,K,P>::solve(const L & linO, VecType & x, 
					   const VecType & b, const T & tol)
{

  // Initialize working data structure...

  T zero(0);    // zero element of type T
  VecType r(b); // Residual vector initialized to RHS vector, b
  
  // Compute residual due to initial guess x...

  T xn = norm2(x);
  if(xn > zero) r -= prod(linO, x);

  T beta = norm2(r);
  T rn = beta;

  // Construct Krylov suspace...

  krylovSpace.buildSpace(linO, r, tol); /* Arnoldi or Housholder */

  m = krylovSpace.size();

  // Get the projection of A (i.e. 'linO') on the Krylov subspace...

  HessType hess(m, true);
  krylovSpace.projA(hess);

  // Compute correction vector...

  VecType y(m);
  VecType z(n);
  rn = projectionScheme.solve(beta, hess, y); /* GMRES or Galerkin projection */
  krylovSpace.map(y, z);

  // Apply correction to intial guess...

  x += z;

  // Return residual norm...

  return rn;
	
}
