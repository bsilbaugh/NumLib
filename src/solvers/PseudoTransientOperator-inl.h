/*! \file PseudoTransientOperator-inl.h
 */

template<class T, class NL>
PseudoTransientOperator<T,NL>::PseudoTransientOperator(Size n, NL & f_):
	 dtau(1.0),        /* Default pseudo time step size */
	 tscale(1.0/dtau), /* initialize to time scaling to Implicit Euler */
	 uk(n),
	 w(n),
	 f(f_)
{
	 // Set default initial condition to zero...

	 uk.zero();
	 w.zero();

	 DEBUG_PRINT_VAR( dtau );
	 DEBUG_PRINT_VAR( tscale );
}

template<class T, class NL>
PseudoTransientOperator<T,NL>::~PseudoTransientOperator()
{
	 /* nothing to delete */
}

template<class T, class NL> inline
void PseudoTransientOperator<T,NL>::stepSize(Real dtau_)
{
	 dtau = dtau_;
}

template<class T, class NL> inline
Real PseudoTransientOperator<T,NL>::stepSize() const
{
	 return dtau;
}

template<class T, class NL>
void PseudoTransientOperator<T,NL>::setInitialConditions(const VecType & u0)
{
	 // Set time scaling to implicit euler...

	 ASSERT(dtau > 0.0);

	 tscale = 1.0/dtau;

	 // Reset work vector...

	 w.zero();

	 // Set reference solution...

	 uk = u0;
}

template<class T, class NL>
Real PseudoTransientOperator<T,NL>::nextTimeLevel(const VecType & u)
{

	 ASSERT( dtau > 0.0 );

	 DEBUG_PRINT_VAR( dtau );

	 // Compute steady residual norm of previous time level...

	 Real rn = norm2( u - uk )/dtau;

	 // Update work vector...

	 w = uk;
	 w -= u;
	 w *= (0.5/dtau);

	 // Pivot reference solution...

	 uk = u;

	 // Update tscale to correspond to BDF2...

	 tscale = 1.5/dtau;

	 return rn;
}

template<class T, class NL>
void PseudoTransientOperator<T,NL>::eval(const VecType & u, VecType & r)
{
	 // Evaluate F(u)...

	 f.eval(u, r);

	 // Add contribution from pseudo transient ...

	 r -= tscale*(u - uk);
	 r -= w;
}
