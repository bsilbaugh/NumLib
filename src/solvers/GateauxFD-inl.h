
template<class T, class NL>
GateauxFD<T,NL>::GateauxFD(NL & f_, const VecType & u_, const VecType & fu_):
	 eps(1.0E-5),
	 f(f_), 
	 u(u_), 
	 fu(fu_)
{
	 //eps = std::sqrt(eps);
}

template<class T, class NL>
GateauxFD<T,NL>::~GateauxFD()
{
	 /* nothing to delete */
}

template<class T, class NL>
void GateauxFD<T,NL>::eval(const VecType & v, VecType & dfv) const
{

	 ASSERT( v.size() == dfv.size() );
	 ASSERT( &v != &dfv );

	 // Compute step size...

	 Real h = eps;

#ifdef GATEAUX_USE_ADAPTIVE_STEP_SIZE

	 dfv = abs(v); /* temporarily store |v| in dfv */

	 Real uTv = prod(u,v);
	 Real uTv_abs = fabs(uTv);
	 Real uTv_sign = sign(uTv);
	 Real vn = norm2(v);

	 ASSERT( vn > 0 );

	 h = (eps/vn)*max(uTv_abs, 1.0E-6)*uTv_sign;

	 ASSERT( fabs(h) > 0 );

#endif

	 DEBUG_PRINT_VAR( h );

	 // Compute perturbed solution...

	 VecType upert(u);
	 upert += h*v;
	 f.eval(upert, dfv); /* dfv = f(u+h*v) */

	 // Evaluate finite difference...

	 dfv -= fu; /* dfv = f(u+h*v) - f(u)     */
	 dfv /= h;  /* dfv = [f(u+h*v) - f(u)]/h */
}
