/*! \file EulerParameterVector.h
 */

#ifndef EULERPARAMETERVECTOR_H
#define EULERPARAMETERVECTOR_H

#include "TensorR2.h"
#include "TensorExpressions.h"

namespace numlib{ namespace tensor{

//! Model of the Euler parameter vector
class EulerParameterVector
{
public:

	 EulerParameterVector(Real q1_=0.0, Real q2_=0.0, Real q3_=0.0, Real q4_=0.0);

	 EulerParameterVector(const TensorR2 & r);

	 EulerParameterVector(const TensorR1 & e, Real theta);

	 EulerParameterVector(const EulerParameterVector & other);

	 ~EulerParameterVector();

	 EulerParameterVector & operator=(const EulerParameterVector & other);

	 //! Returns the effective rotation angle about the rotation axis
	 Real rotationAngle() const;

	 //! Returns the rotation axis (normalized to unity)
	 TensorR1 rotationAxis() const;

	 Real & operator()(Index i);

	 const Real & operator()(Index i) const;

private:

	 Real q1;

	 Real q2;

	 Real q3;

	 Real q4;

};

}}//::numlib::tensor

#endif
