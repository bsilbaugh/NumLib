/*! \file NewtonKrylov-inl.h
 */

template<class T, class NL, class K, class P>
NewtonKrylov<T,NL,K,P>::NewtonKrylov(Size n_, Size mmax_, Size lmax_, Real tol_):
	 n(n_), 
	 mmax(mmax_), 
	 lmax(lmax_), 
	 tol(tol_), 
	 r(n_), 
	 rn(0),	 
	 krylov(n_,mmax_)
{
}

template<class T, class NL, class K, class P> inline
void NewtonKrylov<T,NL,K,P>::tolerance(Real tol_)
{
	 tol = tol_;
}

template<class T, class NL, class K, class P> inline
Real NewtonKrylov<T,NL,K,P>::tolerance() const
{
	 return tol;
}

template<class T, class NL, class K, class P>
T NewtonKrylov<T,NL,K,P>::newSequence(NL & f, const VecType & u0)
{

	 // Compute initial residual...

	 DEBUG_PRINT( "Computing initial residual" );

	 f.eval(u0, r);
	 rn = norm2(r);

	 DEBUG_PRINT_VAR( rn );

	 return rn;
}

template<class T, class NL, class K, class P>
T NewtonKrylov<T,NL,K,P>::iter(NL & f, VecType & u)
{

	 // Clear convergent histories for linear solver...

	 DEBUG_PRINT("Clearing linear convergence history...");

	 convHist.clear();
	 dimHist.clear();

	 // Create approximate Gateaux operator...

	 GateauxFD<T,NL> gateaux(f, u, r); /* r = f(u) */

	 // Set initial guess for linear problem...

	 VecType du(n);
	 du.zero();

	 /* Since initial guess, du, is set to zero, the current nonlinear residual
	  * is equal to the initial residual of the linearized system */

	 // Solve for Newton correction...

	 DEBUG_PRINT( "Solving for newton correction..." );

	 r *= -1.0;
	 Index liter = 0;
	 Size m;
     while( (rn > tol) and (liter++ < lmax) )
	 {
		  rn = krylov.solve(gateaux, du, r, tol);
		  m = krylov.subSpaceDim();

		  DEBUG_PRINT_VAR( rn );
		  DEBUG_PRINT_VAR( m );

		  convHist.push_back(rn);
		  dimHist.push_back(m);
	 }

	 DEBUG_PRINT_VAR( du );

	 u += du;

	 // Update nonlinear residual...

	 DEBUG_PRINT( "Updating nonlinear residual" );

	 f.eval(u, r); /* r = f(u) */
	 rn = norm2(r);

	 DEBUG_PRINT_VAR( rn );

	 return rn;

}

template<class T, class NL, class K, class P>
const RealList & NewtonKrylov<T,NL,K,P>::krylovConvHist() const
{
	 return convHist;
}

template<class T, class NL, class K, class P>
const SizeList & NewtonKrylov<T,NL,K,P>::krylovDimHist() const
{
	 return dimHist;
}
