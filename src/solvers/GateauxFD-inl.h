
template<class T, class NL>
GateauxFD<T,NL>::GateauxFD(NL & f_, const VecType & u_, const VecType & fu_):
	 eps(1.0E-9),
	 f(f_), 
	 u(u_), 
	 fu(fu_)
{
	 eps = std::sqrt(eps);
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

	 dfv = abs(v); /* temporarily store |v| in dfv */

	 Real uTv = prod(u,v);
	 Real uTv_abs = fabs(uTv);
	 Real uTv_sign = 1;
	 if(uTv < 0) uTv_sign = -1;
	 Real vn = norm2(v);

	 ASSERT( vn > 0 );

	 h = (eps/vn)*max(uTv_abs, eps)*uTv_sign;

	 ASSERT( fabs(h) > 0 );

	 DEBUG_PRINT_VAR( h );

	 // Compute perturbed solution and evaluate finite difference...

	 VecType upert(v);
	 upert *=  h;
	 upert +=  u;
	 f.eval(upert, dfv); /* dfv = f(u+h*v) */

	 dfv -= fu;   /* dfv = f(u+h*v) - f(u)     */
	 dfv /= h;    /* dfv = [f(u+h*v) - f(u)]/h */

}
