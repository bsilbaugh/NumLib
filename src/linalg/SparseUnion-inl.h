/*! \file SparseUnion-inl.h
 */

SparseUnion::SparseUnion(const SparsePattern & spL,
					     const SparsePattern & spR)
{
  // Alloc data...

  nLU = spL.size();
  nRU = spR.size();
  
  kLU = new Index[nLU];
  kRU = new INdex[nRU];

  // Compute union...

  findUnion(spL, spR);

}

SparseUnion::~SparseUnion()
{
  DEBUG_PRINT( "SparseUnion destructor called" );
  delete[] kLU;
  delete[] kRU;
}

SparseUnion::findUnion(const SparsePattern & spL,
					   const SparsePattern & spR)
{

  // Alloc working memory...

  Size nL = spL.size();
  Size nR = spR.size();
  Size nbuff = nL + nR;
  Index* buff = new Index[nbuff];

  // Find union...

  Index kL, kR, kU;

  kL = kR = kU = 0;

  while( (kL < nL) and (kR < nR) )
	{
	  if( spL(kL) < spR(kR) )
		{
		  buff[kU] = spL(kL);
		  kLU[kL] = kU;
		  ++kU;
		  ++kL;
		}
	  else if( spL(kL) > spR(kR) )
		{
		  buff[kU] = spR(kR);
		  kRU[kR] = kU;
		  ++kU;
		  ++kR;
		}
	  else /* left and right are equal */
		{
		  buff[kU] = spL(kL); // = spR(kR)
		  kLU[kL] = kU;
		  kRU[kR] = kU;
		  ++kU;
		  ++kL;
		  ++kR;
		}
	}
  
  // Transfer any remaining values...

  while (kL < nL)
	{
	  buff[kU] = spL(kL);
	  kLU[kL] = kU;
	  ++kU;
	  ++kL;
	}

  while (kR < nR)
	{
	  buff[kU] = spR(kR);
	  kRU[kR] = kU;
	  ++kU;
	  ++kR;
	}

  // Set number of non-zeros of union...

  Size nnU = kU;

  // Create sparsity pattern for union...

  spU = SparseUnion(nnU);
  for(Index k=0; k<nnU; ++k)
	{
	  spU(k) = buff[k];
	}

  // Free working memory...
  delete[] buff; buff=0;
  
}
