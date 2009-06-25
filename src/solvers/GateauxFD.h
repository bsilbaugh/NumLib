/*! \file GateauxFD.h
 */

#ifndef GATEAUXFD_H
#define GATEAUXFD_H

#include "../linalg/Vector.h"

namespace numlib{ namespace solver{

//! Finite difference model of a Gateaux derivative operator
/*!
 *  Computes the Gateaux derivative of F:R^N -> R^N at vector u
 *  with respect to vector v; i.e.
 *  
 *     D[f(u)]v = [f(u + h * v) - f(u)]/h + O(h)
 *
 *  The strategy for computing the step size, h, is based on 
 *  Brown and Saad (Brown, Peter N., Youcef Saad. "Hybrid Krylov 
 *  Methods for Nonlinear Systems of Equations." SIAM J. Sci. Stat. 
 *  Comput. Vol. 11, No. 3, pp. 450-481, May 1990).
 */
template<class T, class NL>
class GateauxFD
{
public:

	 typedef linalg::Vector<T> VecType;

	 //! Creates a approximate Gateaux operator for nonlinear operator f
	 /*!
	  *  f := Nonlinear operator to be differentiated
	  *  u := Vector to evaluate point for the Gateaux derivative
	  *  fu := Value of f(u)
	  *
	  *  Note: fu is passed as an input argument since most applications
	  *  will have already evaluted f(u) (e.g. as the residual of some
	  *  discrete operator) prior to computing its Gateaux derivative.
	  *  This saves a potentially costly function evaluation.
	  */
	 GateauxFD(NL & f_, const VecType & u_, const VecType & fu_);

	 ~GateauxFD();

	 //! Evaluates the Gateaux derivative of f(u) with respect to v
	 /*!
	  *  Arguments:
	  *  v := Vector to differentiate f(u) with respect to
	  *  dfv := Finite difference result
	  */
	 void eval(const VecType & v, VecType & dfv) const;

private:

	 DISALLOW_COPY_AND_ASSIGN( GateauxFD );

	 //! Approximate round-off error in the evaluation of f(u)
	 Real eps;

	 //! Nonlinear operator f(u)
	 NL & f;

	 //! "Typical" value of u (see Brown and Saad)
	 VecType typu;

	 //! Vector to in which the derivative is evaluated
	 const VecType & u;

	 //! Value of nonliner operator f evaluated at u, i.e. f(u).
	 const VecType & fu;

};

#include "GateauxFD-inl.h"

//! Linear operator wrapper function for GateauxFD
template<class T, class NL> inline
linalg::Vector<T> prod(const GateauxFD<T,NL> & gateaux, const linalg::Vector<T> & v)
{
	 linalg::Vector<T> Jv(v.size());
	 gateaux.eval(v, Jv);
	 return Jv;
}

}}//::numlib::solver

#endif
