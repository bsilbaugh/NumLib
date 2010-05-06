/*! \file optimization_error_codes.h
 *  \brief enum defining error codes
 */

#ifndef OPTIMIZATION_ERROR_CODES_H
#define OPTIMIZATION_ERROR_CODES_H

namespace numlib{ namespace optimization{

//! Standard error code values and meanings used by NumLib optimizers
/*!
 *  SUCCESS............. a local minimum was found
 *  NO_MIN.............. no minimum could be found
 *  MULTIPLE_MIN........ multiple minima were detected
 *  EXCEEDED_MAX_ITER... exceeded user specified iteration limits
 *  ERROR............... a generic error occurred - stop execution
 *
 *  When checking error codes it is strongly recommended that
 *  the code value be implicitly checked by comparing against
 *  the defined enum values instead of the associated integer value.
 *  New error codes may be introduced which cause the associated
 *  integer values to be redefined.
 *
 */
enum ErrorCode{ SUCCESS, ERROR, NO_MIN, MULTIPLE_MIN, EXCEEDED_MAX_ITER };

}}//::numlib::optimization

#endif
