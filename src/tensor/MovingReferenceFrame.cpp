/*! \file MovingReferenceFrame.cpp
 */

#include "MovingReferenceFrame.h"

namespace numlib{ namespace tensor{

MovingReferenceFrame::MovingReferenceFrame():
	 ReferenceFrame(),
	 x(0,0,0),
	 v(0,0,0),
	 omega(0,0,0)
{}

MovingReferenceFrame::MovingReferenceFrame(const TensorR1 & e1_,
										   const TensorR1 & e2_,
										   const TensorR1 & e3_):
	 ReferenceFrame(e1_,e2_,e3_),
	 x(0,0,0),
	 v(0,0,0),
	 omega(0,0,0)
{}

MovingReferenceFrame::MovingReferenceFrame(const TensorR2 & r):
	 ReferenceFrame(r),
	 x(0,0,0),
	 v(0,0,0),
	 omega(0,0,0)
{}

MovingReferenceFrame::MovingReferenceFrame(const MovingReferenceFrame & other):
	 ReferenceFrame(other),
	 x(other.x),
	 v(other.v),
	 omega(other.omega)
{}

MovingReferenceFrame::~MovingReferenceFrame()
{
	 /* nothing to delete */
}

MovingReferenceFrame & MovingReferenceFrame::operator=(const MovingReferenceFrame & other)
{
	 if(&other == this)
		  return *this;

     ReferenceFrame::operator=(other);
	 x = other.x;
	 v = other.v;
	 omega = other.omega;

	 return *this;
}

}}//::numlib::tensor
