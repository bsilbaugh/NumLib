/*! \file TensorR2.h
 *  \brief TensorR1 class definition
 */

#ifndef TENSORR1_H
#define TENSORR1_H

#include <iostream>
#include <iomanip>
#include <cmath>

#include "../base/numlib-config.h"
#include "../base/debug_tools.h"
#include "../base/DivisionByZero.h"
#include "../base/IndexError.h"

namespace numlib{ namespace tensor{

// Forward declaration of TensorR2 to avoid cyclic header dependency
class TensorR2;
   
//! Model of a rank 1 tensor (vector) in R3
/*!
 *	This class is modeled after a tensor of rank 1 in a space of dimension
 *	3. As all other tensors in defined in this library, this class is 
 *	intented to represent a tensor in the symbolic sense of classical
 *	tensor analysis. Thus, we do not distinquish between contravariant 
 *	tensor or covariant vectors; strickly speaking, covariant "vectors"
 *	are really one-forms anyway.
 */
class TensorR1
{
public:
        
	//! Initializes vector to zero
	TensorR1();

	//! Initialize vector using provided Cartesian components
	TensorR1(Real x, Real y, Real z);

	//! Obligatory virtual destructor
	virtual ~TensorR1() {}
	
	//! Set/return Cartesian component (index: 1, 2, 3)
	Real & operator()(Index i);

	//! Set/return Cartesian component value (index: 1, 2, 3)
	Real operator()(Index i) const;

	//! Sets all components to zero
	TensorR1 & zero();
        
	// In-place arithmetic operations

	//! In-place addition	
	TensorR1 & operator+=(const TensorR1 & u);

	//! In-place subtraction
	TensorR1 & operator-=(const TensorR1 & u);

	//! In-place multiplication by a scalar
	TensorR1 & operator*=(const Real a);

	//! In-place division by a scalar
	TensorR1 & operator/=(const Real a);
        
	//! Dot product
	friend
	Real dot(const TensorR1 & u, const TensorR1 & v);

	//! Dot product
	friend
	TensorR1 dot(const TensorR2 & A, const TensorR1 & u);

	//! Dot product
	friend
	TensorR1 dot(const TensorR1 & u, const TensorR2 & A);

    //! Cross product
	friend
	TensorR1 cross(const TensorR1 & u, const TensorR1 & v);

	//! Standard vector norm in R3 := Euclidian norm = L2-norm
	/*!
	 *	Computes L2 norm of u. Implimenting this as a friend function
	 *	as opposed to a member function enables the computation of
	 *	the L2-norm of a vector expression; i.e.
	 *
	 *	           a = norm2( cross(u,v) );
	 *
	 *	which is more readable than
	 *
	 *	           a = (cross(u,v)).norm2();
	 */
	friend
	Real norm(const TensorR1 & u);

	friend
	Real v_dot_A_dot_u(const TensorR1 & v, const TensorR2 & A, const TensorR1 & u);

	//! Maps to skew symmetric tensor of rank 2
	friend
	TensorR2 skew(const TensorR1 & u);

	//! Constructs the tensor product of two vectors
	friend
	TensorR2 dyad(const TensorR1 & u, const TensorR1 & v);
      
	//! ostream output
	friend 
	std::ostream & operator<<(std::ostream & os, const TensorR1 & V);

protected:
       
    //! Cartesian components	
	Real x, y, z;
 
};
    
}} // numcpp::tensor

#include "TensorR1-inl.h"

#endif
