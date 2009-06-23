/*! \file NewtonKrylov-inl.h
 */

template<class T, class NL, class K, class P>
NewtonKrylov<T,NL,K,P>::NewtonKrylov(Size n_, Size mmax_, Size lmax_, Size nlmax_):
  n(n_), mmax(mmax_), lmax(lmax_), nlmax(nlmax_), krylov(n_,mmax_)
{
}

template<class T, class NL, class K, class P>
T NewtonKrylov<T,NL,K,P>::iter(const NL & f, const VecType & u0)
{
  
  // Compute initial residual...

  r = f(u0);
  rn = norm2(r);

  return rn;
}

template<class T, class NL, class K, class P>
T NewtonKrylov<T,NL,K,P>::iter(const NL & f, const VecType & u)
{
  
  // Set initial guess for linear problem...

  VecType du(n);
  du.zero();

  // Solve for Newton correction...

  liter = 0;
  while( (rn > tol) and (liter++ < lmax) )
	rn = krylov.solve(gateux, du, -r, tol);

  u += du;

  // Update nonlinear residual...

  r = f(u);
  rn = norm2(r);

  return rn;

}
