
template<class T, class NL>
GateauxFD<T,NL>::GateauxFD(NL & f_, const VecType & u_, const VecType & fu_):
	 f(f_), typu(u_.size()), u(u_), fu(fu_), eps(1.0E-6)
{
	 typu = abs(u);
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

	 dfv = abs(v); /* temporarily store |v| in dfv */

	 Real uTv = prod(u,v);
	 Real uTv_abs = fabs(uTv);
	 Real uTv_sign = sign(uTv);
	 Real typuTv = prod(typu, dfv);
	 Real vn = norm2(v);

	 ASSERT( vn > 0 );

	 Real h = eps;

	 if(uTv_abs > 0)
		  h = (eps/vn)*max(uTv_abs, typuTv)*uTv_sign;
//		  h = (eps/vn)*max(uTv_abs, typuTv); /* Seems to work better ? */

	 ASSERT( fabs(h) > 0 );

	 DEBUG_PRINT_VAR( h );

	 // Compute perturbed solution...

	 VecType upert(u);
	 upert += h*v;
	 f.eval(upert, dfv); /* dfv = f(u+h*v) */

	 // Evaluate finite difference...

	 dfv -= fu; /* dfv = f(u+h*v) - f(u)     */
	 dfv /= h;  /* dfv = [f(u+h*v) - f(u)]/h */
}
