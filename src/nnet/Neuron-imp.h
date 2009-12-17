/*! \file Neuron-imp.h
 */

#define WEIGHT_IC_SF 1.0E-2

namespace numlib{ namespace nnet{

template<class VectorType, class ActFuncType>
Neuron<VectorType, ActFuncType>::Neuron(const ActFunc& prototype, 
		Size nu_, Size nx_):
	f(prototype),
	nu(nu_),
	nx(nx_),
	wx(nx_),
	wu(nu_)
{
	// Initialize weights to random values...

	randomSeed();
	for(Index i=0; i<nx; ++i)
		wx(i) = randomNumber()*WEIGHT_IC_SF;

	randomSeed();
	for(Index i=0; i<nu; ++i)
		wu(i) = randomNumber()*WEIGHT_IC_SF;

}

template<class VectorType, class ActFuncType>
Neuron<VectorType,ActFuncType>::Neuron(const Neuron& other):
	f(other.f),
	nu(other.nu),
	nx(other.nx),
	wx(other.wx),
	wu(other.wu)
{
}

template<class VectorType, class ActFuncType>
Neuron<VectorType,ActFuncType>::~Neuron()
{
	/* nothing to delete */
}

template<class VectorType, class ActFuncType>
Neuron<VectorType,ActFuncType>& Neuron<VectorType,ActFuncType>::operator=(const Neuron& other)
{
	if(&other == this) return *this;

	f = other.f;
	nu = other.nu;
	nx = other.nx;
	wx = other.wx;
	wu = other.wu;

	return *this;
}

template<class VectorType, class ActFuncType>
void Neuron<VectorType,ActFuncType>::inputSize(Size nu_)
{
	nu = nu_;
	wu.resize(nu);

	randomSeed();
	for(Index i=0; i<nu; ++i)
		wu(i) = randomNumber()*WEIGHT_IC_SF;

}

template<class VectorType, class ActFuncType> inline
Size Neuron<VectorType,ActFuncType>::inputSize() const
{
	return nu;
}

template<class VectorType, class ActFuncType>
void Neuron<VectorType,ActFuncType>::stateSize(Size nx_)
{
	nx = nx_;
	wx.resize(nx);

	randomSeed();
	for(Index i=0; i<nx; ++i)
		wx(i) = randomNumber()*WEIGHT_IC_SF;

}

template<class VectorType, class ActFuncType> inline
Size Neuron<VectorType,ActFuncType>::stateSize() const
{
	return nx;
}

template<class VectorType, class ActFuncType>
void Neuron<VectorType,ActFuncType>::inputWeights(const Vector& w)
{
	ASSERT( w.size() == nu );

	wu = w;
}

template<class VectorType, class ActFuncType> inline
const VectorType& Neuron<VectorType,ActFuncType>::inputWeights() const
{
	return wu;
}

template<class VectorType, class ActFuncType>
void Neuron<VectorType,ActFuncType>::stateWeights(const Vector& w)
{
	ASSERT( w.size() == nx );

	wx = w;
}

template<class VectorType, class ActFuncType> inline
const VectorType& Neuron<VectorType,ActFuncType>::stateWeights() const
{
	return wx;
}

template<class VectorType, class ActFuncType>
Real Neuron<VectorType,ActFuncType>::eval(const Vector& u, const Vector& x)
{
	Real v(0.0);

	for(Index i=0; i<nx; ++i)
		v += wx(i)*x(i);

	for(Index i=0; i<nu; ++i)
		v += wu(i)*u(i);

	return f(v);

}

}}//::numlib::nnet
