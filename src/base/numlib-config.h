/*! \file numlib-config.h
 *  \brief Header defining data type definitions used throughout NumLib
 *  
 *   It is anticipated that compilation of NumLib on multiple platforms
 *   may require ad-hoc tweaking of the intrisic data types used by 
 *   NumLib components. Thus, all of the intrisic C/C++ data types
 *   are aliased here to a local name.
 */

#ifndef NUMLIB_CONFIG_H
#define NUMLIB_CONFIG_H

#include <cmath>
#include <list>

namespace numlib{

//! default floating point type for real numbers
/*!
 *	This typedef enables global selection of single/double precision.
 *	In addition, automatic differentiation could be implimented by
 *	replacing this typedef with an appropriate class definition with
 *	overloaded arithmetic operators.
 */
typedef double Real;

//! default array index type
/*!
 *	This typedef allows tayloring of integer type used for array
 *	indicies as well as adding clarity to code.
 */
typedef size_t Index;

//! default array size type
/*!
 *	This typedef is used primarily for code clarity.
 */
typedef size_t Size;

//! default signed integer
/*!
 *	Use this integeter type for general integer computation. For array
 *	indicies use index_t.
 */
typedef long int Int;

//! default unsigned signed integer
/*!
 *	Use this integer type for general unsigned integer computation.
 *	An example might be bit interleaving.
 */
typedef unsigned long int UInt;

//! List for Real types
typedef std::list<Real> RealList;

//! List for Index types
typedef std::list<Index> IndexList;

//! List for Size types
typedef std::list<Size> SizeList;

//! default boolean type
typedef bool Bool;

/*** Common basic functions ****/

using std::cos;

using std::sin;

//! Computes the absolute value of a number
inline
Real abs(const Real & x)
{
	 return std::fabs(x);
}

//! Returns the maximum value of a pair of Real numbers
inline
Real max(const Real & a, const Real & b)
{
	 if(b > a)
		  return b;
	 else
		  return a;
}

//! Returns the sign of a floating point number
inline
Real sign(const Real & val)
{
	 return val/std::fabs(val);
}

}

//! Checks if a value is zero
inline
bool is_zero(const Real x)
{
	Real one(1.0);
	return (one + x == one);
}

#endif
