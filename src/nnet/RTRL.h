/*! \file RTRL.h
 */

#ifndef RTRL_H
#define RTRL_H

#include "../array/Array1D.h"
#include "../array/Array2D.h"
#include "FCRNN.h"

namespace numlib{ namespace nnet{

//! Implements the Real-Time Recurrent Learning (RTRL) algorithm
/*!
 *  RTRL is a gradient based learning algorithm developed by Williams 
 *  and Zipser (1989) for continuous real-time training of fully connected 
 *  recurrent networks. As this is a gradient based algorithm, it
 *  may be inadequate for systems with long term dependencies. In
 *  addition, RTRL is derived on the assumtion that the weights are
 *  adjusted on a time scale that is much slower than the system to
 *  be modeled. Hence, it is not a ``rapid'' learning algorithm per
 *  sey; small learning rates may be needed for stability.
 */
template<class VecType=array::Array1D<Real> >
class RTRL
{
public:

	typedef VecType Vector;
	typedef FCRNN<VecType,HypTan> FCRNN;

	RTRL(FCRNN* nnet_);

	void learningParam(Real eta_) {eta = eta_;}

	Real learningParam() const {return eta;}

	void eval(const Vector& u, const Vector& y_true, Vector& y);

private:

	typedef array::Array2D<Vector> Dxdw;

	//! Learning rate parameter
	Real eta;

	//! Gradient set
	Dxdw dxdwu;

	//! Gradient set
	Dxdw dxdwx;

	//! Fully Connected Recurrent Network to be trained
	FCRNN* nnet;

	void correctWeights(const Vector& err);

	void updateGradients(const Vector& u, const Vector& xn);

};

}}//::numlib::nnet

#include "RTRL-imp.h"

#endif
