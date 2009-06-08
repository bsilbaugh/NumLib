/*! \file SparseUnion.h
 */

#ifndef SPARSEUNION_H
#define SPARSEUNION_H

#include "SparsePattern.h"

namespace numlib{ namespace linalg{

class SparseUnion
{
public:

  SparseUnion(const SparsePattern & spL, const SparsePattern & spR);

  ~SparseUnion();

  const SparsePattern & sparsePattern() {return spU;}

  Index leftIndex(Index k) {return kLU[k];}

  Index rightIndex(Index k) {return kRU[k];}

private:

  DISALLOW_COPY_AND_ASSIGN( SparseUnion<KeyType> );

  SparsePattern spU;

  //! Number of elements from "left" pattern which are in the union
  Size nLU;

  //! Number of elements from "right" pattern which are in the union
  Size nRU;

  //! Map from "left" key index to union key index
  Index* kLU;

  //! Map from "right" key index to union key index
  Index* kRU;

  //! Finds the union of "left" and "right" sparsity patterns
  void findUnion(const SparsePattern & spL, const SparsePattern & spR);

};

#include "SparseUnion-inl.h"

}}//::numlib::linalg

#endif
