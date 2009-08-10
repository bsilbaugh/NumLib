/*! \file TensorExpressions.h
 *  \brief A collection of commonly used tensor expressions
 *
 *  \todo Find a better way of obtaining tensor components for purposes
 *  of evaluating tensor expressions. Current use of friend functions works,
 *  but breaks encapsulation.
 */

#ifndef TENSOREXPRESSIONS_H
#define TENSOREXPRESSIONS_H

#include "TensorR1.h"
#include "TensorR2.h"

namespace numlib{ namespace tensor{

//! Computes the dot product between a tensors of rank 2 and rank 1
/*!
 *	Evaluates \f[ \mathbf{v} = \mathbf{A} \mathbf{u} \f]
 */
TensorR1 dot(const TensorR2 & A, const TensorR1 & u);

//! Computes the dot product between a tensors of rank 1 and rank 2
/*!
 *	Evaluates \f[ \mathbf{v} = \mathbf{u} \cdot \mathbf{A} \f]
 */
TensorR1 dot(const TensorR1 & u, const TensorR2 & A);

//! Evaluates the expression \f$ c = \mathbf{v} \cdot \mathbf{A} \mathbf{u} \f$
Real v_dot_A_dot_u(const TensorR1 & v, const TensorR2 & A, const TensorR1 & u);

//! Maps a vector to a skew symmetric tensor
/*!
 *
 *  The skew symmetric tensor is defined such that 
 *
 *  	\f[ \mathbf{U} = skew(\mathbf{u}) 
 *  	     \Rightarrow 
 *  	     \mathbf{U} \mathbf{v} = \mathbf{u} \times \mathbf{v} \f]
 *
 *	In component form, the skew symmetric tensor is
 *
 *		\f[ [skew(\mathbf{u})]\ 
 *		     =  \left[
 *		     \begin{array}{rrr}
 *				 0   & -u_3 &  u_2 \\
 *				 u_3 &  0   & -u_1 \\
 *				-u_2 &  u_1 &  0   \\
 *			\end{array}
 *			\right]
 *		\f]
 */
inline
TensorR2 skew(const TensorR1 & u)
{
	return TensorR2( 0.0, -u.z,  u.y,
			         u.z,  0.0, -u.x,
			        -u.y,  u.x,  0.0);
}

inline
TensorR1 unskew(const TensorR2 & t)
{
	// Verify that t is in fact a skew symmetric tensor when in debug mode
	ASSERT( t.a11 == 0.0 );
	ASSERT( t.a22 == 0.0 );
	ASSERT( t.a33 == 0.0 );
	ASSERT( t.a12 == -t.a21 );
	ASSERT( t.a13 == -t.a31 );
	ASSERT( t.a23 == -t.a33 );

	// Unskew the skew tensor
	return TensorR1(t.a32, t.a13, t.a21);
}

inline
Real trace(const TensorR2 & t)
{
	 return t.a11 + t.a22 + t.a33;
}

//! Constructs the tensor product of two vectors, \f$ \mathbf{A} = \mathbf{u} \otimes \mathbf{v} \f$
inline
TensorR2 dyad(const TensorR1 & u, const TensorR1 & v)
{
	Real u1 = u.x;
	Real u2 = u.y;
	Real u3 = u.z;
	Real v1 = v.x;
	Real v2 = v.y;
	Real v3 = v.z;
	return TensorR2(u1*v1, u1*v2, u1*v3,
			        u2*v1, u2*v2, u2*v3,
					u3*v1, u3*v2, u3*v3);
}

}} // ::numlib::tensor

#endif
