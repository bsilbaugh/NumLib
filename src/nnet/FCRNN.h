/*! \file FCRNN.h
 */

#ifndef FCRNN_H
#define FCRNN_H

#include "../array/PointerArray.h"
#include "Neuron.h"

namespace numlib{ namespace nnet{

//! Fully Connected Recurrent Neural Network
/*!
 *  Models a Fully Connected Recurrent Neural Nework.
 *
 *  If a bias is to be used, the input vector, u, should be sized
 *  to include one additional element which contains a fixed value
 *  of +1. The weights corresponding to this element will correspond 
 *  to the bias value. This implicit treatement of the bias term
 *  enables the user the freedom to use or not use a bias without
 *  any additional program logic. Any element of the u vector may
 *  be chosen to be bias element; however, choosing the last element 
 *  of u to be the bias element will probably result in the least 
 *  amount of confusion by other users of your code.
 *
 *  Mechnisms for training the network (i.e. selection of weight values) 
 * 	are not provided by this class. Identification of appropriate weight 
 * 	values, activation function parameters, and number of hidden units 
 * 	is to be handled by external means. In-situ adjustment of these 
 * 	parameters by external network training algorithms is permissible 
 * 	and expected. This class does provide handles (pointers) to each 
 * 	neuron within the network to facilitate	training.
 */
template<class VecType, class ActFuncType=HypTan>
class FCRNN
{
public:

	typedef ActFuncType ActFunc;
	typedef VecType Vector;
	typedef Neuron<Vector,ActFuncType> Neuron;

	FCRNN(const Neuron& prototype, Size nin, Size nout, Size nhide);

	FCRNN(const FCRNN & other);

	~FCRNN();

	FCRNN& operator=(const FCRNN& other);

	//! Returns size of input vector
	Size inputSize() const {return nu;}

	//! Returns size of output vector
	Size outputSize() const {return ny;}

	//! Returns size of network state vector
	Size stateSize() const {return nx;}

	//! Resets state vector to default initial condition
	void resetState();

	//! Sets network state vector
	void state(const Vector& xo) {x = xo;}

	//! Returns reference to network state vector
	const Vector& state() const {return x;}

	//! Returns pointer to ith neuron
	Neuron* neuron(Index i) {return neurons[i];}

	//! Returns pointer to ith neuron
	const Neuron* neuron(Index i) const {return neurons[i];}

	//! Maps input vector, u, to output vector, y
	void eval(const Vector& u, Vector& y);

private:

	//! Number of output nodes
	Size ny;

	//! Number of input nodes
	Size nu;

	//! Number of states (number of hidden + output nodes)
	Size nx;

	//! State vector
	Vector x;

	//! Array of neurons
	array::PointerArray<Neuron> neurons;

};

}}//::numlib::nnet

#include "FCRNN-imp.h"

#endif
