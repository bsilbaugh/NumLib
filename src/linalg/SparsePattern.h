/*! \file SparsePattern.h
 */

#ifndef SPARSEPATTERN_H
#define SPARSEPATTERN_H

#include "numlib-config.h"
#include "debug_tools.h"

namespace numlib{ namespace linalg{

template< class KeyType >
class SparsePattern
{
public:

  //! Create a sparsity pattern for "nn" non-zero elements
  SparsePattern(Size nn_=0);

  //! Copy constructor (deep copy)
  SparsePattern(const SparsePattern & other);

  //! Destructor
  ~SparsePattern();

  //! Assignment (deep copy)
  SparsePattern & operator=(const SparsePattern & other);

  //! Returns the number of non-zero elements
  Size size();

  //! Sets/returns non-zero element key value by index
  /*! 
   *  Index range is [0,nn-1]. All key values are assumed to be sorted
   *  and "increase" with index value.
   */
  KeyType & operator[](Index k);

  //! Returns non-zero element key value by index
  const KeyType & operator[](Index k) const;

private:

  // Number of non-zero elements
  Size nn;

  // Array of non-zero element keys
  KeyType* keys;

  // copies data from "other" to "this"
  void copy(const SparsePattern & other);

};

#include "SparsePattern-inl.h"

}}//::numlib::linalg

#endif
