/*! \file ReferenceFrame.h
 *  \brief ReferencFrame class definition
 */

#ifndef REFERENCEFRAME_H
#define REFERENCEFRAME_H

#include "TensorR1.h"
#include "TensorR2.h"

namespace numlib{ namespace tensor{

//! Orthonormal Cartesian basis defining the orientation of a reference frame
class ReferenceFrame
{
public:

	//! Constructs a reference frame with cardinal basis
	ReferenceFrame();

	//! Constructs a reference frame from triad of orthonormal basis vectors
	ReferenceFrame(const TensorR1 e1_, const TensorR1 & e2_, const TensorR1 & e3_);

	//! Constructs a rotated reference frame defined by a rotation tensor
	/*!
	 *  The rotation tensor 'r' is taken to be a map which rotates any
	 *  vector in the cardinal frame to the rotated reference frame.
	 */
	ReferenceFrame(const TensorR2 & r);

	//! Copy constructor
	ReferenceFrame(const ReferenceFrame & other);

	~ReferenceFrame();

	//! Assignment
	ReferenceFrame & operator=(const ReferenceFrame & other);

	//! Returns the ith unit basis vector
	const TensorR1 & operator()(Index i) const;

private:

	TensorR1 e1;
	TensorR1 e2;
	TensorR1 e3;

	void copy(const ReferenceFrame & other);

};

}}//::numlib::tensor

#include "ReferenceFrame-inl.h"

#endif
