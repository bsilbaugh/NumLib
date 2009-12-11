/*! \file Neuron.h
 */

#ifndef NEURON_H
#define NEURON_H

#include "../base/random.h"
#include "HypTan.h"

namespace numlib{ namespace nnet{

//! Model of a single artificial neuron
template<class VectorType, class ActFuncType=HypTan>
class Neuron
{
public:

	typedef ActFuncType ActFunc;
	typedef VectorType Vector;

	//! Initializes a neuron with nx+nu input nodes
	Neuron(const ActFunc& prototype, Size nu_=0, Size nx_=0);

	//! Copy constructor (deep copy)
	Neuron(const Neuron& other);

	//! Frees all internally held memory
	~Neuron();

	//! Assignment operator (deep copy)
	Neuron& operator=(const Neuron& other);

	//! Set size of input vector
	/*!
	 *  WARNING: Resizing input vector results in resetting of
	 *  the input weight vector.
	 */
	void inputSize(Size nu_);

	//! Returns size of input vector
	Size inputSize() const;

	//! Sets size of state vector
	/*!
	 * 	WARNING: Resizing state vector results in resetting of
	 * 	the state weight vector.
	 */
	void stateSize(Size nx_);

	//! Returns size of state vector
	Size stateSize() const;

	//! Sets input vector weight values
	void inputWeights(const Vector& w);

	//! Returns reference to input weight vector
	const Vector& inputWeights() const;

	//! Sets state vector weight values
	void stateWeights(const Vector& w);

	//! Returns reference to state weight vector
	const Vector& stateWeights() const;

	//! Evaluates neuron mapping (u,x) to scalar output value
	Real eval(const Vector& u, const Vector & x);

private:

	//! Activation function
	ActFunc f;

	//! Input vector size
	Size nu;

	//! State vector size
	Size nx;

	//! Weight vector associated with the state vector
	Vector wx;

	//! Weight vector associated with the input vector
	Vector wu;

};

}}//::numlib::nnet

#include "Neuron-imp.h"

#endif
