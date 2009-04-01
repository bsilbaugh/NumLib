/*! \file QuadRule.h
 *  \brief QuadRule struct definition
 */

#ifndef QUADRULE_H
#define QUADRULE_H

#include "../base/numlib-config.h"
#include "../array/Array1D.h"

namespace numlib{ namespace integration{

//! Struct containing quadrature weights and locations
/*!
 *	Quadrature locations are given in normalized cooridinates,
 *	\f$ \xi \in [-1, 1] \f$.
 */
struct QuadRule
{
	//! Normalized quadrature locations
	array::Array1D<Real> grid;

	//! Quadrature weights
	array::Array1D<Real> weights;

	//! Initializes data structure for n-point quadrature scheme
	QuadRule(Size n):grid(n),weights(n) {}
};

}} //::numlib::integration

#endif
