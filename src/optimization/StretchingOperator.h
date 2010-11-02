/*! \file StretchingOperator.h
 *	\brief StretchingOperator class template definition
 */

#ifndef STRETCHING_OPERATOR_H
#define STRETCHING_OPERATOR_H

namespace numlib{ namespace optimization{

template<class F, class V>
class StretchingOperator
{
public:

	typedef F FunctionType;
	typedef V VectorType;

	//! Constructs a stretching operator for a multi-variate cost function f
	/*!
	 *	This object with hold a reference to f for the duration of its
	 *	life. Do not delete f prior to the deletion of this object.
	 */
	StretchingOperator(FunctionType& f_, const VectorType& x_lmin_, const Real fx_lmin_):
		f(f_),
		gamma_1(1.0),
		gamma_2(1.0),
		mu(1.0),
		x_lmin(x_lmin_),
		fx_lmin(fx_lmin_)
	{}

	//! Sets tunning parameters
	void tunningParams(const Real gamma_1_, const Real gamma_2_, const Real mu_)
	{gamma_1 = gamma_1_; gamma_2 = gamma_2_; mu = mu_;}

	//! Sets local minimum where function is to be stretched relative to
	void localMinimum(const VectorType& x_lmin_, const Real fx_lmin_)
	{
		x_lmin = x_lmin_;
		fx_lmin = fx_lmin_;
	}

	Real operator()(const VectorType& x)
	{

		Real gx = f(x);

		if(gx < fx_lmin) return gx;

		Real swch = sgn(gx - fx_lmin) + 1.0;

		Real r = norm2(x - x_lmin);

		gx += gamma_1*r*swch;

		return gx + gamma_2*swch/tanh(mu*(gx - fx_lmin));
	}

private:

	// Reference to cost function
	F& f;

	// Tuning parameters
	Real gamma_1, gamma_2, mu;

	// Location of local minima
	VectorType x_lmin;

	// Cost at local minima
	Real fx_lmin;

};

}}//::numlib::optimization

#endif
