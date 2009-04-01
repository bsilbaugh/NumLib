/*! \file Quadrature.h
 *  \brief Numerical quadrature function library
 */

#ifndef QUADRATURE_H
#define QUADRATURE_H

#include "QuadRule.h"
#include "../base/NumLibError.h"

namespace numlib{ namespace integration{

//! Generates a quadrature rule for an polynomial of degree "n"
/*!
 *	Currently, the table only supports degrees 1 through 19.
 *
 *	The quadrature rules are for functions of a single variable (i.e. 1D domain).
 *	As is standard convention, all weights include the jacobian scaling from
 *	the problem domain to the normalized domain [-1, 1].
 *
 *	Higher dimensional quadrature rules can be formulated using the 1D rules
 *	defined here. However, for dimensions much higher than 1 Gauss quadrature
 *	is not as cost effective as some other schemes (Hughs 2000).
 */
QuadRule GaussQuadTable(Index n);

//! Returns the Gauss quadrature rule associated with n quad points
/*!
 *  Employs the same quadrature rules as GaussQuadTable, except the
 *  lookup is performed by number of quad points instead of polynomial
 *  degree.
 */
QuadRule InvGaussQuadTable(Index n);

}} //::numlib::integration

#endif
