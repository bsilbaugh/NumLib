/*! \file Vector.h
 *  \brief uBLAS typedefs
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "../base/debug_tools.h"
#include "../base/numlib-config.h"

namespace numlib{ namespace linalg{

//! Unbounded dense vector
typedef boost::numeric::ublas::vector<Real> Vector;

//! Unbounded sparse vector
typedef boost::numeric::ublas::compressed_vector<Real> SparseVec;

//! Vector range proxy
typedef boost::numeric::ublas::vector_range<Vector> VectorRange;

//! Vector slice proxy
typedef boost::numeric::ublas::vector_slice<Vector> VectorSlice;

//! Unbounded zero vector
typedef boost::numeric::ublas::zero_vector<Real> ZeroVec;

//! Unbounded unit vector
typedef boost::numeric::ublas::unit_vector<Real> UnitVec;

//! L2-norm
using boost::numeric::ublas::norm_2;

}}
#endif
