/*! \file Minimum1D.h
 *  \file Minimum1D class definition
 */

#ifndef MINIMUM_1D_H
#define MINIMUM_1D_H

namespace numlib{ namespace optimization{

class Minimum1D
{
public:

	Minimum1D(Real xopt_, Real fopt_):
		xopt(xopt_), fopt(fopt_),
		xL(xopt), fL(fopt),
		xU(xopt), fU(fopt)
	{}

	void design(Real x, Real f) { xopt = x; fopt = f; }

	void lowerBound(Real x, Real f) { xL = x; fL = f; }

	void upperBound(Real x, Real f) { xU = x; fU = f; }

	Real design() const {return xopt;}

	Real lowerBound() const {return xL;}

	Real upperBound() const {return xU;}

	Real cost() const {return fopt;}

	Real costAtLowerBound() const {return fL;}

	Real costAtUpperBound() const {return fU;}

private:

	// Estimated location of minimum
	Real xopt;

	// Minumum cost
	Real fopt;

	// Lower and upper bound of minimum
	Real xL, xU;

	// Cost at lower and upper bounds
	Real fL, fU;

};

}}//::numlib::optimization

#endif
