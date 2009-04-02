/*! \file TensorR2.h
 *  \brief Rank 2 tensor class definition
 */

#ifndef TENSORR2_H
#define TENSORR2_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include "../base/numlib-config.h"
#include "../base/debug_tools.h"
#include "../base/DivisionByZero.h"
#include "../base/IndexError.h"

namespace numlib{ namespace tensor{

// forward declaration to avoid cyclic header dependency
class TensorR1;

class TensorR2
{
public:

	//! Initializes tensor to zero
	TensorR2();

	//! Initializes tensor with specified Cartesian components
	TensorR2(Real t11, Real t12, Real t13,
			 Real t21, Real t22, Real t23,
			 Real t31, Real t32, Real t33);

	TensorR2(const TensorR2 & other);

	~TensorR2();

	TensorR2 & operator=(const TensorR2 & other);

	//! Set/resturn Cartesian component (index base 1)
	Real & operator()(Index i, Index j);

	//! Returns Cartesian component (index base 1)
	Real operator()(Index i, Index j) const;

	//! Sets all components to zero
	TensorR2 & zero();

	//! In-place addition
	TensorR2 & operator+=(const TensorR2 & other);

	//! In-place subtraction
	TensorR2 & operator-=(const TensorR2 & other);

	//! In-place multiplication by a scalar
	TensorR2 & operator*=(Real a);

	//! In-place division by a scalar
	TensorR2 & operator/=(Real a);

	//! Returns the transpose of a rank 2 tensor
	friend
	TensorR2 transpose(const TensorR2 & t);

	//! Returns the vector associated with a skew symmetric tensor
	friend 
	TensorR1 unskew(const TensorR2 & t);

	//! Inner/dot product of rank 2 tensors
	friend
	TensorR2 dot(const TensorR2 & t1, const TensorR2 & t2);

	//! Dot product
	friend
	TensorR1 dot(const TensorR2 & A, const TensorR1 & u);

	//! Dot product
	friend
	TensorR1 dot(const TensorR1 & u, const TensorR2 & A);

	friend
	Real v_dot_A_dot_u(const TensorR1 & v, const TensorR2 & A, const TensorR1 & u);

	//! ostream output
	friend
	std::ostream & operator<<(std::ostream & os, const TensorR2 & t);

private:

	Real a11, a12, a13;
	Real a21, a22, a23;
	Real a31, a32, a33;

	Real*** indexMap;

	void copy(const TensorR2 & other);

	void initIndexMap();

	void delIndexMap();

};

}} //::numlib::tensor

#include "TensorR2-inl.h"

#endif
