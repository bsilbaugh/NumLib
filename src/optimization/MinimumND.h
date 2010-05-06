/*! \file MinimumND.h
 *  \brief MinimumND template definition
 */

#ifndef MINIMUM_ND_H
#define MINIMUM_ND_H

namespace numlib{ namespace optimization{

template<class V>
class MinimumND
{
public:

	MinimumND(Size dim):
		n(dim),xopt(n),fopt(1.0E10)
	{
		xopt.zero();
	}

	MinimumND(const V& xopt_, Real fopt_):
		n(xopt_.size()),xopt(xopt_), fopt(fopt_)
	{}

	Size size() const {return n;}

	//! Sets the estimated optimal "design"
	void design(const V& xopt_, Real fopt_) 
	{
		ASSERT( xopt.size() == n );
		xopt = xopt_; 
		fopt = fopt_;
	}

	//! Returns the optimal "design"
	const V& design() const {return xopt;}

	//! Returns the cost associated with the optimal design
	Real cost() const {return fopt;}

private:

	Size n;

	V xopt;

	Real fopt;

};

}}//::numlib::optimization

#endif
