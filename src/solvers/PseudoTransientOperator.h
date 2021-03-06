/*! \file PseudoTransientOperator.h
 */

#ifndef PSEUDOTRANSIENTOPERATOR_H
#define PSEUDOTRANSIENTOPERATOR_H

#include "../base/nocopy.h"
#include "../linalg/Vector.h"

namespace numlib{ namespace solver{

//! Pseudo-transient continuation operator for solving nonlinear algebraic systems
/*!
 *  This converts the problem of solving F(u) = 0 into the pseudo-transient problem
 *  du/dt - F(u) = 0, which has F(u) = 0 as its steady solution. The 
 *  pseudo-transient term du/dt is implicitly discretized using BDF2 (Euler Implicit
 *  for the first step). 
 *
 *  The pseudo transient residual, R(u) = du/dt - F(u), may be reduced to zero at 
 *  each pseudo time step using a quasi-Newton method (e.g. NewtonKrylov). In 
 *  some cases the pseudo-transient residual need not be tightly converged at 
 *  each pseudo time step for the overall scheme to converge to F(u) = 0; e.g. 
 *  it may be sufficient to advance the pseudo-time level with each newton 
 *  iteration.
 *
 *  In regards to the choice of pseudo time step size, selecting very large values
 *  will effectively remove the contribution of the pseudo transient and the
 *  operator will degenerate to R(u) = F(u). Provided the initial solution estimate
 *  is close to the solution, this may be desirable. However, for initial gueses
 *  which are outside the ball of convergence of the iterative algorithm (e.g.
 *  Newton's method), then a small value should be selected. In practice, choosing
 *  the step size to be on the order of 1.0/||F(u0)||, where u0 is the initial
 *  solution estimate, seems to work well. It should also be noted that if
 *  Newton's method is being used it is possible that the Jacobian of F(u) will 
 *  become either singular or ill-conditioned (even for a "good" initial guess). 
 *  Use of pseudo-transient continuation will help to ensure that the Jacobian
 *
 *  The nonlinear operator F, is expected to be implemented in the same manner as 
 *  outlined in the NewtonKrylov documentation. The class which implements F, is 
 *  to be provided as a template parameter. 
 *  
 */
template<class T, class NL>
class PseudoTransientOperator
{
public:

	 typedef linalg::Vector<T> VecType;

	 PseudoTransientOperator(Size n, NL & f_):
	    dtau(1.0),        /* Default pseudo time step size */
	    tscale(1.0/dtau), /* initialize to time scaling to Implicit Euler */
	    uk(n),
	    w(n),
	    r_steady(n),
	    f(f_)
    {
    	 // Set default initial condition to zero...
    
    	 uk.zero();
    	 w.zero();
    	 r_steady.zero();
    
    	 DEBUG_PRINT_VAR( dtau );
    	 DEBUG_PRINT_VAR( tscale );
    }

	 ~PseudoTransientOperator() { /* nothing to delete */ }

	 //! Sets pseudo time step size
	 void stepSize(Real dtau_) { dtau = dtau_; }

	 //! Returns pseudo time step size
	 Real stepSize() const { return dtau; }

	 //! Sets initial conditions for pseudo march to steady state
	 /*!
	  *  This should be set to the initial solution estimate which would
	  *  typically be used to start the quasi-Newton iteration. In the case
	  *  of dual-time stepping, u0, should be the predicted solution at n+1
	  *  (physical) time level.
	  */
	 void setInitialConditions(const VecType & u0)
     {
     	 // Set time scaling to implicit euler...
     	 ASSERT(dtau > 0.0);
     	 tscale = 1.0/dtau;
     
     	 // Reset work vector...
     	 w.zero();
     
     	 // Set reference solution...
     	 uk = u0;
     }
	 
	 //! Advances the pseudo time level
	 /*!
	  *  Advances the pseudo time level by one (i.e. from k to k+1). 
	  *  The current solution is to be provided as input argument and
	  *  will be used as the "previous" solution corresponding to the 
	  *  k pseudo time level.
	  *
	  *  The 2-norm of the steady residual, F(u), is computed from the
	  *  change in the solution and is returned as an rvalue.
	  *
	  */
	 Real nextTimeLevel(const VecType & u)
     {
     	 ASSERT( dtau > 0.0 );

     	 DEBUG_PRINT_VAR( dtau );
          
     	 // Pivot reference solution...
     	 uk = u;
    
         // Return norm... 
     	 return norm2( r_steady );
     }

	 //! Evaluates the pseudo-transient residual, r = d(u)/dt - F(u)
	 void eval(const VecType & u, VecType & r)
     {
     	 // Evaluate F(u)...
     	 f.eval(u, r_steady);
     
     	 // Add contribution from pseudo transient ...
     	 r = r_steady - (u - uk)/dtau;
     
     	 DEBUG_PRINT("Writting u, r, r_steady to log files...");
     	 DEBUG_LOG("pseudo_tran_res_operator-u.dat", u);
     	 DEBUG_LOG("pseudo_tran_res_operator-r.dat", r);
     	 DEBUG_LOG("pseudo_tran_res_operator-r_steady.dat", r_steady);
     }

private:

	 DISALLOW_COPY_AND_ASSIGN( PseudoTransientOperator );

	 //! Pseudo time step size
	 Real dtau;

	 //! Pseudo time scale factor
	 Real tscale;

	 //! Solution corresponding to the kth pseudo time level
	 VecType uk;

	 //! Working vector associated with the difference between k and k-1 time levels
	 VecType w;

	 //! Steady residual vector
	 VecType r_steady;

	 //! Reference to nonlinear operator class which implements F(u).
	 NL & f;

};

}}//::numlib::solver

#endif
