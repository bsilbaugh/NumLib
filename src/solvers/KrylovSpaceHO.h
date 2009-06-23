/*! \file KrylovSpaceHO.h
 */

#ifndef KRYLOVSPACEHO_H
#define KRYLOVSPACEHO_H

namespace numlib{ namespace linalg{


//! Krylov subspace model with implements Householder Orthogonalization
/*!
 *  Given exact arithmetic operations, this is equivolent to Arnoldi's
 *  orthogonalization algorithm. However, for finite precision artithmetic
 *  Householder's algorithm has been shown to be less sensitive to round
 *  off errors.
 *
 *  \todo Implement this scheme
 */
template<class T>
class KrylovSpaceHO
{
};

}}//::numlib::linalg

#endif
