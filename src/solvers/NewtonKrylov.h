/*! \file NewtonKrylov.h
 */

#ifndef NEWTONKRYLOV_H
#define NEWTONKRYLOV_H

#include <list>
#include "Krylov.h"
#include "GateauxFD.h"

namespace numlib{ namespace solver{

//! Newton-Krylov solver framework for nonlinear systems
/*!
 *  This template may be used with any type, f, which implements the nonlinear
 *  operator interface f(u,r), where u is the approximate solution vector and
 *  r is the (returned) residual vector corresponding to u. Note, the alternative
 *  interface r = f(u) is more syntatically pleasing; however, this results in
 *  frequent construction, copying, and deletion of potentially large vectors.
 *
 *  This solver does not employ any internal globalization strategies such as
 *  linesearch backtracking or model trust region techniques. It is anticipated
 *  that this solver will primarily be used in the context of IVP's with implicit
 *  time discretization. Constructing an intial guess that falls within the sphere
 *  of convergence for Newton's method can often be achieved using an predictor
 *  based on an explicit time advancement scheme or--if the time step is small
 *  enough--using the solution from the previous time level.
 *
 *  If nonlinear convergence posses an issue, techniques such as psuedo transient
 *  continuation (e.g. dual time stepping) and nonlinear pre-conditioning can be
 *  implemented as wrappers around this solver class. See Knoll and Keys for
 *  details (Knoll, D.A., and D.E. Keys. "Jacobian-free Newton-Krylov methods:
 *  a survey of approaches and applications." Journal of Computational Physics
 *  193 (2004) 357-397.)
 *
 *  \todo Implement linear preconditioning and scaling.
 */
template<class T, class NL, class K, class P>
class NewtonKrylov
{
public:

	 typedef linalg::Vector<T> VecType;

	 NewtonKrylov(Size n_, Size mmax_, Size lmax_, Real tol_):
	 n(n_), mmax(mmax_), lmax(lmax_), tol(tol_), r(n_), rn(0), krylov(n_,mmax_)
     { }

	 //! Sets convergence tolerance
	 void tolerance(Real tol_) { tol = tol_; }

	 //! Returns convergence tolerance currently being used by solver
	 Real tolerance() const { return tol; }

	 //! Initialize a new non-linear iteration sequence
	 /*!
	  *  The residual 2-norm of the nonlinear system, f(u), is returned
	  */
	 T newSequence(NL & f, const VecType & u0)
     {
     	 // Compute initial residual...
     
     	 DEBUG_PRINT( "Computing initial residual" );
     
     	 f.eval(u0, r);
     	 rn = norm2(r);
     
     	 DEBUG_PRINT_VAR( rn );
     
     	 return rn;
     }

	 //! Executes a single non-linear iteration
	 /*!
	  *  Upon input, u is expected to contain the previous (initial)
	  *  solution estimate. Upon return, u is overwritten with the corrected
	  *  solution estimate. The residual 2-norm of the nonlinear system, f(u), 
	  *  is returned as rvalue.
	  */
	 T iter(NL & f, VecType & u)
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
     
     		  DEBUG_PRINT_VAR( tol );
     		  DEBUG_PRINT_VAR( lmax );
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

	 //! Returns a reference to the internally held residual vector
	 /*!
	  *  The life of the residual vector is guarenteed for the life
	  *  of this solver. This is primarily provided for solution error
	  *  estimation and monitoring.
	  */
	 const VecType & residual() { return r; }

	 const RealList & krylovConvHist() const { return convHist; }

	 const SizeList & krylovDimHist() const { return dimHist; }

private:

	 DISALLOW_COPY_AND_ASSIGN( NewtonKrylov );

	 //! Space dimension
	 Size n;

	 //! Max sub-space dimension...
	 Size mmax;

	 //! Max number of linear iterations (sub-space restarts)
	 Size lmax;

	 //! Stopping criteria on residual 2-norm
	 Real tol;

	 //! Residual vector
	 VecType r;

	 //! Residual vector 2-norm
	 T rn;

	 //! Linear Krylov Solver
	 Krylov<T,GateauxFD<T,NL>,K,P> krylov;

	 //! Linear Krylov convergent history
	 RealList convHist;

	 //! Linear Krylov space dimension history
	 SizeList dimHist;

};

}}//::numlib::sovler

#endif

