
#include "solverLU.h"

namespace numlib{ namespace linalg{

Vector solveLU(const Matrix & A, const Vector & b)
{

	using boost::numeric::ublas::lu_factorize;
	using boost::numeric::ublas::lu_substitute;

	int N = b.size();
	Vector x(N);
	Matrix LU(N,N);
	PermutationMatrix P(N);

	LU = A;

	lu_factorize(LU,P);
	x = b;
	lu_substitute(LU,P,x);

	return x;
}

}}
