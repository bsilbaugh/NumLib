/*! \file Matrix.h
 *  \brief uBLAS typedefs -- no sense reinventing the wheel...
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "../base/debug_tools.h"
#include "../base/numlib-config.h"

namespace numlib{ namespace linalg{

//! Unbounded dense matrix
typedef boost::numeric::ublas::matrix<Real> Matrix;

//! Unbounded sparse matrix -- uses compressed storage scheme
typedef boost::numeric::ublas::compressed_matrix<Real> SparseMat;

//! Unbounded zero matrix
typedef boost::numeric::ublas::zero_matrix<Real> ZeroMat;

//! Permutation matrix
typedef boost::numeric::ublas::permutation_matrix<Index> PermutationMatrix;

using boost::numeric::ublas::norm_inf;

}} //::numlib::linalg

#endif
