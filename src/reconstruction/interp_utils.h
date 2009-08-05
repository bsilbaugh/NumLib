/*! \file interp_utils.h
 */

#ifndef INTERP_UTILS_H
#define INTERP_UTILS_H

namespace numlib{ namespace reconstruction{

//! Finds partitions of y which belong to the intervals defined by adjacent elements in x
/*!
 *  Given two arrays, x and y, containing ordered sets of numbers the partitions of
 *  y are found such that the following equivolence relations hold:
 *  - for 0 <= j < p(0): y(j) < x(0)
 *  - for p(i) <= j < p(i+1): x(i) <= y(j) < x(i+1)
 *  - for p(nx-1) < j < p(nx): x(nx-1) <= y(j)
 *
 *  NOTES:
 *
 *  1. The arrays x and y are assumed to be sorting in ascending order:
 *       x(0) < x(1) < ... x(i) < .... < x(nx-1)
 *       y(0) <= y(1) <= ... y(i) <= .... <= y(ny-1)
 *
 *  2. The size of the partitioning array, p, must be equal to the size of 
 *     x (i.e. p.size() = x.size()).
 */
template<class ArrayT, class IndexArrayT>
void partitionByIntervals(const ArrayT & x, const ArrayT & y, IndexArrayT & p)
{
	 // Get sizes...

	 Size nx = x.size();
	 Size ny = y.size();

	 ASSERT( p.size() == nx );

	 // Find partitions...

	 Index j(0);

	 for(Index i=0; i<nx; ++i)
	 {
		  p(i) = j;
		  while( y(j) < x(i) )
			   p(i) = ++j;
	 }

}

}}//::numlib::reconstruction

#endif
