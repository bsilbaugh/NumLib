
template<class T, class NL>
NewtonArnoldi<T,NL>::NewtonArnoldi(Size n_, Size mmax_, Size lmax_, Real tol_):
	 NewtonKrylov<T,NL,KrylovSpaceAO<T,GateauxFD<T,NL> >,GalerkinProjection<T> >(
		  n_, mmax_, lmax_, tol_)
{
}
