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
typedef unsigned int Index;

//! default array size type
/*!
 *	This typedef is used primarily for code clarity.
 */
typedef unsigned int Size;

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

//! default boolean type
typedef bool Bool;

}

#endif
