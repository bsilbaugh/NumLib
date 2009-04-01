/*! \file solverLU.h
 *  \brief Defines LU solvers for dense systems
 */

#ifndef SOLVERLU_H
#define SOLVERLU_H

#include "Vector.h"
#include "Matrix.h"

namespace numlib{ namespace linalg{

//! Solves the linear system A*x = b using LU decomposition
/*!
 *	Contents of coefficient matrix, A, and right hand side vector
 *	b are preserved. Note, if repeated solves are required for the
 *	same coefficient matrix, may want to consider using a different
 *	solver which saves the LU factorization.
 */
Vector solveLU(const Matrix & A, const Vector & b);

//! Enables use of LU decomp to solve sparse systems
/*!
 *	This is provided for debugging/testing purposes. For production
 *	runs, iterative methods are strongly recommended for solving
 *	sparse systems (e.g. conjugate gradient, BICGSTAB, SOR, GMRES, etc).
 */
inline
Vector solveLU(const SparseMat & S, const Vector b)
{
	DEBUG_PRINT( "Copying SparseMat to type of Matrix" );
	Matrix A = S;
	DEBUG_PRINT( "Solving sparse system with LU decomp" );
	return solveLU(A, b);
}

//! Overloaded solve function for dense systems
inline
Vector solve(const Matrix & A, const Vector & b)
{
	return solveLU(A, b);
}

}}

#endif
