/*! \file MovingReferenceFrame.h
 */

#ifndef MOVINGREFERENCEFRAME_H
#define MOVINGREFERENCEFRAME_H

#include "ReferenceFrame.h"

namespace numlib{ namespace tensor{

//! Extends ReferenceFrame type to include linear and rotation motion
class MovingReferenceFrame: public ReferenceFrame
{
public:

	 //! Constructs a moving reference frame with canonical basis
	 MovingReferenceFrame();

	 //! Constructs a moving frame from orthonormal triad
	 /*!
	  *  All kinematic quantities initialized to zero
	  */
	 MovingReferenceFrame(const TensorR1 & e1_, const TensorR1 & e2_, const TensorR1 & e3_);

	 //! Constructs a moving frame as a rotation from the canonical basis
	 MovingReferenceFrame(const TensorR2 & r);

	 //! Copy constructor
	 MovingReferenceFrame(const MovingReferenceFrame & other);

	 virtual
	 ~MovingReferenceFrame();

	 //! Assignment (deep copy)
	 MovingReferenceFrame & operator=(const MovingReferenceFrame & other);

	 //! Sets frame position
	 void position(const TensorR1 & x_) {x = x_;}

	 //! Returns frame position
	 const TensorR1 & position() const {return x;}

	 //! Sets frame velocity
	 void velocity(const TensorR1 & v_) {v = v_;}

	 //! Returns frame velocity
	 const TensorR1 & velocity() const {return v;}

	 //! Sets frame acceleration
	 void acceleration(const TensorR1 & a_) {a = a_;}

	 //! Returns frame acceleration
	 const TensorR1 & acceleration() const {return a;}

	 //! Sets frame material angular velocity
	 void angularVelocity(const TensorR1 & omega_) {omega = omega_;}

	 //! Returns frame material angular velocity
	 const TensorR1 & angularVelocity() const {return omega;}

	 //! Sets frame material angular acceleration
	 void angularAcceleration(const TensorR1 & omega_dot_) {omega_dot = omega_dot_;}

	 //! Returns frame material angular acceleration
	 const TensorR1 & angularAcceleration() const {return omega_dot;}

private:

	 /* REMINDER: orientation vectors contained in base class */
	 
	 //! Position of frame origin
	 TensorR1 x;

	 //! Velocity of frame origin
	 TensorR1 v;

	 //! Acceleration of frame
	 TensorR1 a;

	 //! Material angular velocity of frame
	 TensorR1 omega;

	 //! Material angular acceleration of frame
	 TensorR1 omega_dot;

};

}}//::numlib::tensor

#endif
