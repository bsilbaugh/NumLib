/*! \file lapack_wrapper.h
 *  \brief A high-level C wrapper around selected LAPACK routines.
 */

#ifndef LAPACK_WRAPPER_H
#define LAPACK_WRAPPER_H

#include "../base/numlib-config.h"

#define F77_SUBROUTINE( function_name )\
	function_name##_

/*----------------------------------------------------------------------------*/
/*                                                          LAPACK PROTOTYPES */

extern "C"{

void F77_SUBROUTINE(dgesv)(const long* n, const long* nrhs, double* a, 
		const long* lda, long* ipiv, double* b, const long* ldb, long* info); 

}// extern "C"

/*----------------------------------------------------------------------------*/
/*                                                            LAPACK WRAPPERS */                                                  

namespace numlib{ namespace linalg{

inline
Int lapack_dgesv(const Size n, const Size nrhs, const Real* a, const Size lda,
				 Int* ipiv,	Real* b, const Size ldb)
{
	long n_c(n);
	long nrhs_c(nrhs);
	long lda_c(lda);
	long ldb_c(ldb);
	long info_c(0);
	double* a_c = (double*) a;
	double* b_c = (double*) b;
	long* ipiv_c = (long*) ipiv;

	DEBUG_PRINT_VAR(n_c);
	DEBUG_PRINT_VAR(nrhs_c);
	DEBUG_PRINT_VAR(lda_c);
	DEBUG_PRINT_VAR(ldb_c);
	DEBUG_PRINT_VAR(info_c);

	F77_SUBROUTINE(dgesv)(&n_c, &nrhs_c, a_c, &lda_c, ipiv_c, b_c, &ldb_c, &info_c);

	return info_c;
}

}}//::numlib::linalg

#endif
