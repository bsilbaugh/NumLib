/*! \file FiniteRotations.h
 *  \brief Finite rotations module
 *
 *  A collection of types and functions to simply the modeling of
 *  of finite rotations. For the most part, the types used here are the
 *  primitive tensor data types defined in the tensor library. Notable
 *  exceptions are the rotation parameter vector types. Introduction of
 *  separate types for rotation paramter vectors was done to enable overloading
 *  of library functions which depend on the choice of rotation paramters;
 *  overloading of non-member functions was chosen over implementation as
 *  member functions for the following reasons:
 *
 *  	- Clearer syntax: e.g. R = rot(psi) is clearer thant R = psi.rot()
 *  	- A number of functions are not dependent on the choice of rotation
 *  	  paramters; thus, universal use of non-member functions provides a
 *  	  more consistent functional style throughout.
 *
 *	\todo Add other common paramterizations: Euler Paramters, Euler angles,
 *	Rodrequez paramters, quaternious, pseudo rotation vector, etc
 */

#ifndef FINITEROTATIONS_H
#define FINITEROTATIONS_H

#include <cmath>

#include "TensorR1.h"
#include "TensorR2.h"
#include "ReferenceFrame.h"
#include "TensorExpressions.h"

// Rotation parameter vector types
#include "RotVector.h"
#include "EulerParameterVector.h"

namespace numlib{ namespace tensor{

//! Returns rotation tensor about x-axis
/*!
 *  Positive rotation is defined per "right hand rule"
 */
TensorR2 rotX(Real theta);

//! Returns rotation tensor about y-axis
/*!
 *  Positive rotation is defined per "right hand rule"
 */
TensorR2 rotY(Real theta);

//! Returns rotation tensor about z-axis
/*!
 *  Positive rotation is defined per "right hand rule"
 */
TensorR2 rotZ(Real theta);

//! Maps the rotation vector to the corresponding rotation tensor
TensorR2 rot(const RotVector & rv);

//! Maps the euler parameter vector to the corresponding rotation tensor
/*!
 *  Formulation base on chapter 2 of Amirouche (Amirouche. Fundamentals
 *  of Multibody Dynamics. 2006. Birkhauser Boston.).
 */
TensorR2 rot(const EulerParameterVector & rv);

//! Maps a reference frame to a rotation from the canonical unit basis
TensorR2 rot(const ReferenceFrame & frame);

//! Computes the material (right) incremental rotation vector
void rotInc(const TensorR2 & r, const TensorR2 & r0, RotVector & rvinc);

//! Returns the tensor which maps the rotation vector increment to the local tangent space of R
/*!
 *	This map is most often used to compute curvature (angular velocity)
 *	vector from space (time) derivative of the rotation vector.
 */
TensorR2 tanMap(const RotVector & rv);

//! Returns the Frechet derivative of the tangent map at 'rv' wrt 'drv'
TensorR2 tanMapDer(const RotVector & rv, const RotVector & drv);

//! Maps the time derivative of the rotation vec to the angular velocity
/*!
 *	Note, replacing the time derivative of the rotation vector with its 
 *  derivative along a space curve yields the curvature vector of that
 *  curve.
 */
inline
TensorR1 angVel(const TensorR2 & tmap, const RotVector & rv_dot)
{
	return dot(tmap, rv_dot);
}

//! Maps the time derivative of the rotation vec to the angular velocity
/*!
 *	Note, replacing the time derivative of the rotation vector with its 
 *  derivative along a space curve yields the curvature vector of that
 *  curve.
 */
inline
TensorR1 angVel(const RotVector & rv, const RotVector & rv_dot)
{
	return dot(tanMap(rv), rv_dot);
}

//! Maps the time derivatives of the rotation vector to the angular acceleration
TensorR1 angAcc(const RotVector & rv, const RotVector & rv_dot, const RotVector & rv_ddot);

}} //::numlib::tensor

#endif
