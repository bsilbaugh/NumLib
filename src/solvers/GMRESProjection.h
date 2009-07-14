/*! \file GMRESProjection
 */

#ifndef GMRESPROJECTION_H
#define GMRESPROJECTION_H

namespace numlib{ namespace solver{

template<class T>
class GMRESProjection
{
public:

  typedef HessMatrix<T> HessType;

  //! Computes the Krylov correction such that residual is A-ortho to K
  /*!
   *  This projection condition is effected by finding the minimizer, y*, of
   *  the the residual L2-norm. In principle, this should ensure that the
   *  error vector is also minimized in L2 (i.e. the error is ortho to K).
   *
   *  For use as an "inner" solver of a NewtonKrylov scheme, Brown and Saad
   *  (1990) showed that the GMRES projection gives better "descent directions"
   *  than Arnoldi's method (Galerkin projection scheme). So, in practice,
   *  the expectation is that GMRES will generally be favored over the Galerkin
   *  projection scheme.
   */
  solve(const T & beta, HessType & hess, Vector & y);

};

}}//::numlib::solver

#endif
