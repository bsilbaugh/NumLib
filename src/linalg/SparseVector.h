/*! \file SparsePattern.h
 */

#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include "SparsePattern.h"

namespace numlib{ namespace linalg{

//! Sparse vector template
/*!
 *  Model of a sparse vector which provides efficient storage and arithmetic
 *  operations. Element type, T, is any complete numerical type that is 
 *  initializable to zero; i.e. the expressions, T zero = 0 and T zero(0),
 *  are defined.
 *
 *  Since the sparsity pattern is assumed to be invariant, in-place arithmetic
 *  is restricted to multiplication and division by scalars. All other expressions
 *  which generate a vector are assumed to modify the sparsity pattern, thus the
 *  result must be stored in a new vector. The sparsity pattern of the result is
 *  determined by the particular sparse-vector expression or operator used.
 *
 */
template< class T >
class SparseVector
{
public:

  //! Constructs a sparse vector of dim n, with nn non-zero elements
  SparseVector(Size n_, Size nn);

  //! Copy constructor (deep copy)
  SparseVector(const SparseVector)

  //! Destructor
  ~SparseVector();

  //! Assignment (deep copy)
  SparseVector & operator=(const SparseVector & other);

  /* Container interface */

  //! Vector dimension
  /*!
   *  In general, the vector dimension, n, will be significantly greater
   *  than the number of non-zero entries, nn.
   */
  Size size();

  //! Sets the value of the ith element
  /*!
   *  It is assumed that new elements are initialized according to ascending
   *  index. \todo Allow for random initialization of elements.
   */
  void set(Index i, const T & value);

  const T & operator()(Index i) const;

  /* In-place arithmetic operators */

  SparseVector & operator*=(const T & c);
  
  SparseVector & operator/=(const T & c);

private:

  //! Vector dimension
  /*!
   *  Formal dimension of vector (size of equivolent dense vector). Primarily
   *  used for checking consistency of mathematical expressions.
   */
  Size n;

  //! Next availible insert index
  Index kin;

  //! Vector sparsity pattern
  SparsePattern sp;

  //! Element value array (size nn)
  Array1D<T> val;

  //! Zero element
  T zero;

  //! Deep copy function
  void copy(const SparseVector & other);

};

#include "SparseVector-inl.h"

}}//::numlib::linalg

#endif
