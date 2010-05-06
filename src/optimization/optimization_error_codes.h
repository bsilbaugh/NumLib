/*! \file optimization_error_codes.h
 *  \brief enum defining error codes
 */

#ifndef OPTIMIZATION_ERROR_CODES_H
#define OPTIMIZATION_ERROR_CODES_H

namespace numlib{ namespace optimization{

//! Standard error code values and meanings used by NumLib optimizers
/*!
 *  SUCCESS....... a local minimum was found
 *  NOMIN......... no minimum could be found
 *  MULTIPLEMIN... multiple minima were detected
 *  ERROR......... a generic error occurred - stop execution
 *
 *  When checking error codes it is strongly recommended that
 *  the code value be implicitly checked by comparing against
 *  the defined enum values instead of the associated integer value.
 *  New error codes may be introduced which cause the associated
 *  integer values to be redefined.
 *
 */
enum ErrorCode{ SUCCESS, ERROR, NOMIN, MULTIPLEMIN };

}}//::numlib::optimization

#endif
