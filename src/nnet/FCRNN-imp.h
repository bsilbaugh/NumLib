/*! \file FCRNN-imp.h
 */

namespace numlib{ namespace nnet{

template<class VecType, class ActFuncType>
FCRNN<VecType,ActFuncType>::FCRNN(const Neuron& prototype, Size nin, Size nout, Size nhide):
	ny(nout),
	nu(nin),
	nx(nout+nhide),
	x(nx),
	neurons(nx)
{

	DEBUG_PRINT_VAR( nu );
	DEBUG_PRINT_VAR( ny );
	DEBUG_PRINT_VAR( nx );

	// Initialize neurons...

	Neuron* ptr(NULL);	
	for(Index i=0; i<nx; ++i)
	{
		ptr = new Neuron(prototype);
		ptr->inputSize(nu);
		ptr->stateSize(nx);

		neurons[i] = ptr;
	}
	ptr=NULL;

	// Set default network state...
	
	for(Index i=0; i<nx; ++i)
		x(i) = 0.0;

}

template<class VecType, class ActFuncType>
FCRNN<VecType,ActFuncType>::FCRNN(const FCRNN& other):
	ny(other.ny),
	nu(other.nu),
	nx(other.nx),
	x(other.x),
	neurons(nx)
{
	// Copy neurons -- not just the pointers...

	for(Index i=0; i<nx; ++i)
		neurons[i] = new Neuron( *(other.neurons[i]) );
}

template<class VecType, class ActFuncType>
FCRNN<VecType,ActFuncType>::~FCRNN()
{
	neurons.clear();
}

template<class VecType, class ActFuncType>
FCRNN<VecType,ActFuncType>& 
FCRNN<VecType,ActFuncType>::operator=(const FCRNN& other)
{
	if(&other == this) return *this;

	ny = other.ny;
	nu = other.nu;
	nx = other.nx;
	x = other.x;

	neurons.clear();
	neurons.resize(nx);

	for(Index i=0; i<nx; ++i)
		neurons[i] = new Neuron( *(other.neurons[i]) );

	return *this;
}

template<class VecType, class ActFuncType>
void FCRNN<VecType,ActFuncType>::resetState()
{
	for(Index i=0; i<nx; ++i)
		x(i) = 0.0;
}

template<class VecType, class ActFuncType>
void FCRNN<VecType,ActFuncType>::eval(const Vector& u, Vector& y)
{
	ASSERT( u.size() == nu );
	ASSERT( y.size() == ny );

	// Set output value accounting for unit time delay...

	for(Index i=0; i<ny; ++i)
		y(i) = x(i);

	// Now advance network state to next time level...

	Vector xn(x);
	for(Index i=0; i<nx; ++i)
		x(i) = neurons[i]->eval(u, xn);

}

}}//::nnet
