/*! \file NewtonKrylov.h
 */

#ifndef NEWTONKRYLOV_H
#define NEWTONKRYLOV_H

//! Newton-Krylov solver framework for nonlinear systems
template<class T, class NL, class K, class P>
class NewtonKrylov
{
public:

  NewtonKrylov(Size n_, Size mmax_, Size lmax_);

  //! Initialize a new non-linear iteration sequence
  /*!
   *  The residual 2-norm of the nonlinear system, f(u), is returned
   */
  T newSequence(const NL & f, VecType & u0);

  //! Executes a single non-linear iteration
  /*!
   *  Upon input, u is expected to be initialized to a
   *  The residual 2-norm of the nonlinear system, f(u), is returned.
   */
  T iter(const NL & f, VecType & u);

  //! Returns a pointer to the internally held residual vector
  /*!
   *  The life of the residual vector is guarenteed for the life
   *  of this solver. This is primarily provided for solution error
   *  estimation and monitoring.
   */
  const VecType* residual(){return &r;}

private:

  DISALLOW_COPY_AND_ASSIGN( NewtonKrylov );

  //! Space dimension
  Size n;

  //! Max sub-space dimension...
  Size mmax;

  //! Max number of linear iterations (sub-space restarts)
  Size lmax;

  //! Residual vector
  VecType r;

  //! Residual vector 2-norm
  T rn;

  //! Gateaux operator...
  GateauxFD gateux;

  //! Linear Krylov Solver
  Krylov<T,GateauxFD,K,P> krylov;

};

#endif

