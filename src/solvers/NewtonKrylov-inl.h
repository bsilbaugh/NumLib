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
     while( (rn > tol) and (liter++ < lmax) )
	 {
		  rn = krylov.solve(gateaux, du, r, tol);

		  DEBUG_PRINT_VAR( rn );
	 }

	 u += du;

	 // Update nonlinear residual...

	 DEBUG_PRINT( "Updating nonlinear residual" );

	 f.eval(u, r); /* r = f(u) */
	 rn = norm2(r);

	 DEBUG_PRINT_VAR( rn );

	 return rn;

}
