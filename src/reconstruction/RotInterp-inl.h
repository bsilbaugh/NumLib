/*! \file RotInterp-inl.h
 */

RotInterp<GridType,TensorFieldType>::RotInterp(const GridType& srcGrid, 
											   const GridType& dstGrid):
	nsrc(srcGrid.size()),
	ndst(dstGrid.size()),
	interp(srcGrid,dstGrid)
{
}

RotInterp<GridType,TensorFieldType>::RotInterp(const RotInterp& other):
	nsrc(other.nsrc),
	ndst(other.ndst),
	interp(other.interp)
{
}

RotInterp<GridType,TensorFieldType>::~RotInterp()
{
	/* nothing to delete */
}

RotInterp& 
RotInterp<GridType,TensorFieldType>::operator=(const RotInterp& other)
{
	if(&other == this) return *this;

	nsrc = other.nsrc;
	ndst = other.ndst;
	interp = other.interp;

	return *this;
}

void 
RotInterp<GridType,TensorFieldType>::operator()(const TensorFieldType& srcField,
												const TensorFieldType& dstField)
{
	ASSERT(srcField.size() == nsrc);
	ASSERT(dstField.size() == ndst);

	// Set reference rotation...

	tensor::TensorR2 r0 = srcField(0);

	// Compute rotation increments...

	RotVecField rvsrc(nsrc);
	RotVecField rvdst(ndst);

	for(Index i=0; i<nsrc; ++i)
		tensor::rotInc(srcField(i), r0, rvsrc(i));

	// Interpolate rotation increments...

	interp(rvsrc, rvdst);

	// Compute rotation field...

	for(Index i=0; i<ndst; ++i)
		dstField(i) = tensor::dot(r0, rot(rvdst(i)));

}

