/*! \file ReferenceFrame-inl.h
 *  \brief Implementation of inline ReferenceFrame member functions
 */ 

namespace numlib{ namespace tensor{

inline
ReferenceFrame::ReferenceFrame():
	e1(1.0, 0.0, 0.0),
	e2(0.0, 1.0, 0.0),
	e3(0.0, 0.0, 1.0)
{
}

inline
ReferenceFrame::ReferenceFrame(const TensorR1 e1_, const TensorR1 & e2_, 
		const TensorR1 & e3_):
	e1(e1_), e2(e2_), e3(e3_)
{
}

inline
ReferenceFrame::ReferenceFrame(const TensorR2 & r):
	e1(r(1,1), r(2,1), r(3,1)),
	e2(r(1,2), r(2,2), r(3,2)),
	e3(r(1,3), r(2,3), r(3,3))
{
}

inline
ReferenceFrame::ReferenceFrame(const ReferenceFrame & other)
{
	copy(other);
}

inline
ReferenceFrame::~ReferenceFrame()
{
	/* nothing to delete */
}

inline
ReferenceFrame & ReferenceFrame::operator=(const ReferenceFrame & other)
{
	if(&other != this) copy(other);
	return *this;
}

inline
const TensorR1 & ReferenceFrame::operator()(Index i) const
{
	switch(i)
	{
		case 1: 
			return e1;
		case 2: 
			return e2;
		case 3: 
			return e3;
		default:
			throw IndexError();
	}
}

inline
void ReferenceFrame::copy(const ReferenceFrame & other)
{
	e1 = other.e1;
	e2 = other.e2;
	e3 = other.e3;
}

}}//::numlib::tensor
