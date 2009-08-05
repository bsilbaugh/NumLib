/*! \file LinearPW-inl.h
 */

template<class GridType, class VecFieldType>
LinearPW<GridType,VecFieldType>::LinearPW(const GridType & srcGrid,
										  const GridType & dstGrid):
nsrc(srcGrid.size()), 
ndst(dstGrid.size()), 
basisL(ndst), 
basisR(ndst),
p(nsrc)
{

	 // Find partitions...
	
	 partitionByIntervals(srcGrid, dstGrid, p);

	 // Temporary vars...

	 Real ds;
	 Real c;

	 // Compute extrapolation coefficients for elements without lower bound...

	 DEBUG_PRINT("Computing extrapolation coefficients...");

	 ds = srcGrid(1) - srcGrid(0);
	 for(Index j=0; j<p(0); ++j)
	 {
		  c = (dstGrid(j) - srcGrid(0))/ds;
		  basisL(j) = 1.0 - c;
		  basisR(j) = c;
	 }

	 // Compute interpolation coefficients for bounded elements...
	 
	 DEBUG_PRINT("Computing interpolation coefficients...");
	 DEBUG_PRINT_VAR( nsrc );
	 DEBUG_PRINT_VAR( ndst );
	 for(Index i=0; i<nsrc-1; ++i)
	 {
		  ds = srcGrid(i+1) - srcGrid(i);
		  for(Index j=p(i); j<p(i+1); ++j)
		  {
			   c = (dstGrid(j) - srcGrid(i))/ds;
			   basisL(j) = 1.0 - c;
			   basisR(j) = c;
		  }
	 }

	 // Compute extrapolation coefficients for elements without upper bound...

	 DEBUG_PRINT("Computing extrapolation coefficients...");
	 ds = srcGrid(nsrc-1) - srcGrid(nsrc-2);
	 for(Index j=p(nsrc-1); j<ndst; ++j)
	 {
		  c = (dstGrid(j) - srcGrid(nsrc-2))/ds;
		  basisL(j) = 1.0 - c;
		  basisR(j) = c;
	 }

}

template<class GridType, class VecFieldType>
LinearPW<GridType,VecFieldType>::LinearPW(const LinearPW & other):
  nsrc(other.nsrc),ndst(other.ndst),basisL(other.basisL),basisR(other.basisR)
{
}

template<class GridType, class VecFieldType>
LinearPW<GridType,VecFieldType>::~LinearPW()
{
	 /* nothing to delete */
}

template<class GridType, class VecFieldType>
LinearPW<GridType,VecFieldType> & 
LinearPW<GridType,VecFieldType>::operator=(const LinearPW & other)
{
	 if(&other != this) copy(other);
	 return *this;
}

template<class GridType, class VecFieldType>
void LinearPW<GridType,VecFieldType>::operator()(const VecFieldType & srcField,
												 VecFieldType & dstField)
{

	 ASSERT( srcField.size() == nsrc);
	 ASSERT( dstField.size() == ndst);

	 // Perform extrapolation over interval unbounded to the left...

	 for(Index j=0; j<p(0); ++j)
		  dstField(j) = basisL(j)*srcField(0) + basisR(j)*srcField(1);

	 // Perform interpolation over bounded intervals...

	 for(Index i=0; i<nsrc-1; ++i)
		  for(Index j=p(i); j<p(i+1); ++j)
			   dstField(j) = basisL(j)*srcField(i) + basisR(j)*srcField(i+1);

	 // Peform extrapolation over interval unbounded to the right...

	 for(Index j=p(nsrc-1); j<ndst; ++j)
		  dstField(j) = basisL(j)*srcField(nsrc-2) + basisR(j)*srcField(nsrc-1);

}

template<class GridType, class VecFieldType> inline
void LinearPW<GridType, VecFieldType>::copy(const LinearPW & other)
{
	 nsrc = other.nsrc;
	 ndst = other.ndst;
	 basisL = other.basisL;
	 basisR = other.basisR;
	 p = other.p;
}
