/*! \file RTRL-imp.h
 */

namespace numlib{ namespace nnet{

template<class VecType>
RTRL<VecType>::RTRL(FCRNN* nnet_):
	eta(1.0),
	dxdwu(0,0),
	dxdwx(0,0),
	nnet(nnet_)
{
	ASSERT( nnet != NULL );

	// Get network size and initialize internal data structure...
	
	Size nu = nnet->inputSize();
	Size ny = nnet->outputSize();
	Size nx = nnet->stateSize();

	DEBUG_PRINT_VAR( nu );
	DEBUG_PRINT_VAR( ny );
	DEBUG_PRINT_VAR( nx );

	dxdwu.resize(nx,nu);
	dxdwx.resize(nx,nx);

	for(Index i=0; i<nx; ++i)
	{
		for(Index j=0; j<nu; ++j)
		{
			dxdwu(i,j).resize(nx);
			for(Index k=0; k<nx; ++k)
				dxdwu(i,j)(k) = 0.0;
		}
		for(Index j=0; j<nx; ++j)
		{
			dxdwx(i,j).resize(nx);
			for(Index k=0; k<nx; ++k)
				dxdwx(i,j)(k) = 0.0;
		}
	}

}

template<class VecType>
void RTRL<VecType>::eval(const Vector& u, const Vector& y_true, Vector& y)
{
	ASSERT( u.size() == nnet->inputSize() );
	ASSERT( y_true.size() == nnet->outputSize() );
	ASSERT( y.size() == nnet->outputSize() );

	// Grab snapshot of current network state (time level n)...

	Vector xn(nnet->state());

	// Compute error before network evalutation ...

	Vector err(y_true);

	for(Index j=0; j<err.size(); ++j)
		err(j) -= xn(j); /* equal to y(j) at time level n */

	// Correct weights...

	DEBUG_PRINT( "Correcting weights..." );

	correctWeights(err);

	// Apply ``teacher forcing''...

//	for(Index j=0; j<y_true.size(); ++j)	
//		xn(j) = y_true(j);
//	nnet->state(xn);

	// Evaluate network using corrected weights...

	DEBUG_PRINT( "Evaluating network..." );

	nnet->eval(u, y); /* y is at time level n (same as xn) */

	// Update gradients to correspond to the next time level, n+1...

	DEBUG_PRINT( "Updating gradients..." );

	updateGradients(u, xn);

}

template<class VecType>
void RTRL<VecType>::correctWeights(const VecType& err)
{
	Size nx = nnet->stateSize();
	Size nu = nnet->inputSize();
	Size ny = nnet->outputSize();

	DEBUG_PRINT_VAR( nx );
	DEBUG_PRINT_VAR( nu );
	DEBUG_PRINT_VAR( ny );

	ASSERT( err.size() == ny );

	Vector wu(nu);
	Vector wx(nx);
	for(Index j=0; j<nx; ++j)
	{

		// Get previous weight vector for jth neuron...

		wu = nnet->neuron(j)->inputWeights();
		wx = nnet->neuron(j)->stateWeights();

		ASSERT( wu.size() == nu );
		ASSERT( wx.size() == nx );

		// Correct weight vector for jth neuron...

		DEBUG_PRINT( "Correcting wx..." );

		for(Index i=0; i<nx; ++i)
		{
			const Vector& dxdwji = dxdwx(j,i);
			for(Index k=0; k<ny; ++k)
				wx(i) += eta*err(k)*dxdwji(k);
		}

		DEBUG_PRINT( "Correcting wu..." );

		for(Index i=0; i<nu; ++i)
		{
			const Vector& dxdwji = dxdwu(j,i);
			for(Index k=0; k<ny; ++k)
				wu(i) += eta*err(k)*dxdwji(k);
		}

		// Set update weight vector for jth neuron...

		nnet->neuron(j)->inputWeights(wu);
		nnet->neuron(j)->stateWeights(wx);

	}
}

template<class VecType>
void RTRL<VecType>::updateGradients(const Vector& u, const Vector& xn)
{

	Size nx = xn.size();
	Size nu = u.size();

	Vector phip(nx);

	// Compute derivative of activation function...
	
	/* ASSUMING tanh activation function */

	const Vector& x = nnet->state();

	for(Index j=0; j<nx; ++j)
		phip(j) = 1.0 - x(j)*x(j);

	// Update gradient w.r.t. network state weights...

	Vector tmp(nx);

	for(Index j=0; j<nx; ++j)
	{
		for(Index i=0; i<nx; ++i)
		{

			Vector& dxdwji = dxdwx(j,i);

			for(Index k=0; k<nx; ++k)
			{

				tmp(k) = 0.0;

				const Vector& w = nnet->neuron(k)->stateWeights();
				for(Index r=0; r<nx; ++r) 
					tmp(k) +=  w(r)*dxdwji(r);

			}

			for(Index k=0; k<nx; ++k)
				dxdwji(k) = phip(k)*(x(i) + tmp(k));

		}
	}

	// Update gradient w.r.t. input weights...
	
	for(Index j=0; j<nx; ++j)
	{
		for(Index i=0; i<nu; ++i)
		{
			Vector& dxdwji = dxdwu(j,i);
			dxdwji(j) = phip(j)*u(i);
		}
	}

}

}}//::numlib::nnet
