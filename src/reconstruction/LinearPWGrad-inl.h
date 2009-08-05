/*! \file LinearPWGrad-inl.h
 */

template<class GridType, class VecFieldType>
LinearPWGrad<GridType,VecFieldType>::LinearPWGrad(const GridType & srcGrid,
											  const GridType & dstGrid):
nsrc(srcGrid.size()),
ndst(dstGrid.size()),
basisL(ndst),
basisR(ndst),
p(nsrc)
{

	 // Temporaries...

	 Real ds;
	 Real c;

	 // Find partitions...

	 partitionByIntervals(srcGrid, dstGrid, p);

	 // Compute gradient extrapolation coefficients...

	 DEBUG_PRINT("Computing extrapolation coefficients...");

	 ds = srcGrid(1) - srcGrid(0);
	 c = 1.0/ds;
	 for(Index j=0; j<p(0); ++j)
	 {
		  basisL(j) = -c;
		  basisR(j) =  c;
	 }
	 
	 // Compute gradient interpolation coefficients...

	 DEBUG_PRINT("Computing interpolation coefficients...");

	 for(Index i=0; i<nsrc-1; ++i)
	 {
		  ds = srcGrid(i+1) - srcGrid(i);
		  c = 1.0/ds;
		  for(Index j=p(i); j<p(i+1); ++j)
		  {
			   basisL(j) = -c;
			   basisR(j) =  c;
		  }
	 }

	 // Compute gradient extrapolation coefficients...

	 DEBUG_PRINT("Computing extrapolation coefficients...");

	 ds = srcGrid(nsrc-1) - srcGrid(nsrc-2);
	 c = 1.0/ds;
	 for(Index j=p(nsrc-1); j<ndst; ++j)
	 {
		  basisL(j) = -c;
		  basisR(j) =  c;
	 }

}

template<class GridType, class VecFieldType>
LinearPWGrad<GridType,VecFieldType>::LinearPWGrad(const LinearPWGrad & other):
  nsrc(other.nsrc), ndst(other.ndst), basisL(other.basisL), basisR(other.basisR)
{
}

template<class GridType, class VecFieldType>
LinearPWGrad<GridType,VecFieldType>::~LinearPWGrad()
{
	 /* nothing to delete */
}

template<class GridType, class VecFieldType>
LinearPWGrad<GridType,VecFieldType> & 
LinearPWGrad<GridType,VecFieldType>::operator=(const LinearPWGrad & other)
{
	 if(&other != this) copy(other);
	 return *this;
}

template<class GridType, class VecFieldType>
void LinearPWGrad<GridType,VecFieldType>::operator()(const VecFieldType & srcField,
												     VecFieldType & dstField)
{

	 ASSERT( srcField.size() == nsrc);
	 ASSERT( dstField.size() == ndst);

	 for(Index j=0; j<p(0); ++j)
		  dstField(j) = basisL(j)*srcField(0) + basisR(j)*srcField(1);


	 for(Index i=0; i<nsrc-1; ++i)
		  for(Index j=p(i); j<p(i+1); ++j)
			   dstField(j) = basisL(j)*srcField(i) + basisR(j)*srcField(i+1);

	 for(Index j=p(nsrc-1); j<ndst; ++j)
		  dstField(j) = basisL(j)*srcField(nsrc-2) + basisR(j)*srcField(nsrc-1);
}

template<class GridType, class VecFieldType>
void LinearPWGrad<GridType,VecFieldType>::copy(const LinearPWGrad & other)
{
	 nsrc = other.nsrc;
	 ndst = other.ndst;
	 basisL = other.basisL;
	 basisR = other.basisR;
	 p = other.p;
}
