
#include "Quadrature.h"

namespace numlib{ namespace integration{

QuadRule GaussQuadTable(Index n)
{
	switch (n)
	{
		case 0:
			// drop through
			
		case 1:
			return InvGaussQuadTable(1);

		case 2:
			// drop through

		case 3:
			return InvGaussQuadTable(2);

		case 4:
			// drop through

		case 5:
			return InvGaussQuadTable(3);

		case 6:
			// drop through

		case 7:
			return InvGaussQuadTable(4);

		case 8:
			// drop through

		case 9:
			return InvGaussQuadTable(5);

		case 10:
			// drop through

		case 11:
			return InvGaussQuadTable(6);

		case 12:
			// drop through

		case 13:
			return InvGaussQuadTable(7);

		case 14:
			// drop through

		case 15:
			return InvGaussQuadTable(8);

		case 16:
			// drop through

		case 17:
			// drop through

		case 18:
			// drop through

		case 19:
			return InvGaussQuadTable(10);

		default:
			throw NumLibError();
	}
}

QuadRule InvGaussQuadTable(Index n)
{
	switch(n)
	{
		case 1:
		{

			QuadRule q(1);

			q.grid(0) = 0.0;

			q.weights(0) = 2.0;

			return q;
		}

		case 2:
		{

			QuadRule q(2);

			q.grid(0) = -0.57735026918962573; // -sqrt(1/3)
			q.grid(1) =  0.57735026918962573; //  sqrt(1/3)

			q.weights(0) = 1.0;
			q.weights(1) = 1.0;

			return q;
		}

		case 3:
		{
			QuadRule q(3);

			q.grid(2) =  0.77459667;
			q.grid(1) =  0.0;
			q.grid(0) = -q.grid(2);

			q.weights(2) =  0.55555555;
			q.weights(1) =  0.88888889;
			q.weights(0) =  q.weights(2);

			return q;
		}

		case 4:
		{
			QuadRule q(4);

			q.grid(3) = 0.86113631;
			q.grid(2) = 0.33998104;
			q.grid(1) = -q.grid(2);
			q.grid(0) = -q.grid(3);

			q.weights(3) = 0.34785485;
			q.weights(2) = 0.65214515;
			q.weights(1) = q.weights(2);
			q.weights(0) = q.weights(3);

			return q;
		}

		case 5:
		{

			QuadRule q(5);

			q.grid(4) =  0.90617985;
			q.grid(3) =  0.53846931;
			q.grid(2) =  0.0;
			q.grid(1) = -q.grid(3);
			q.grid(0) = -q.grid(4);

			q.weights(4) = 0.23692689;
			q.weights(3) = 0.47862867;
			q.weights(2) = 0.56888889;
			q.weights(1) = q.weights(3);
			q.weights(0) = q.weights(4);

			return q;
		}

		case 6:
		{

			QuadRule q(6);

			q.grid(5) =  0.93246951;
			q.grid(4) =  0.66120939;
			q.grid(3) =  0.23861918;
			q.grid(2) = -q.grid(3);
			q.grid(1) = -q.grid(4);
			q.grid(0) = -q.grid(5);

			q.weights(5) = 0.17132449;
			q.weights(4) = 0.36076157;
			q.weights(3) = 0.46791393;
			q.weights(2) = q.weights(3);
			q.weights(1) = q.weights(4);
			q.weights(0) = q.weights(5);

			return q;
		}

		case 7:
		{
			QuadRule q(7);

			q.grid(6) =  0.94910791;
			q.grid(5) =  0.74153119;
			q.grid(4) =  0.40584515;
			q.grid(3) =  0.0;
			q.grid(2) = -q.grid(4);
			q.grid(1) = -q.grid(5);
			q.grid(0) = -q.grid(6);

			q.weights(6) = 0.12948497;
			q.weights(5) = 0.27970539;
			q.weights(4) = 0.38183005;
			q.weights(3) = 0.41795918;
			q.weights(2) = q.weights(4);
			q.weights(1) = q.weights(5);
			q.weights(0) = q.weights(6);

			return q;
		}

		case 8:
		{
			QuadRule q(8);

			q.grid(7) =  0.96028986;
			q.grid(6) =  0.79666648;
			q.grid(5) =  0.52553241;
			q.grid(4) =  0.18343464;
			q.grid(3) = -q.grid(4);
			q.grid(2) = -q.grid(5);
			q.grid(1) = -q.grid(6);
			q.grid(0) = -q.grid(7);

			q.weights(7) = 0.10122854;
			q.weights(6) = 0.22238103;
			q.weights(5) = 0.31370665;
			q.weights(4) = 0.36268378;
			q.weights(3) = q.weights(4);
			q.weights(2) = q.weights(5);
			q.weights(1) = q.weights(6);
			q.weights(0) = q.weights(7);

			return q;
		}

		case 9:
			/* \todo 9-point scheme data need to be generated */
			throw NumLibError(); 

		case 10:
		{
			QuadRule q(10);

			q.grid(9) =  0.97390653;
			q.grid(8) =  0.86506337;
			q.grid(7) =  0.67940957;
			q.grid(6) =  0.43339539;
			q.grid(5) =  0.14887434;
			q.grid(4) = -q.grid(5);
			q.grid(3) = -q.grid(6);
			q.grid(2) = -q.grid(7);
			q.grid(1) = -q.grid(8);
			q.grid(0) = -q.grid(9);

			q.weights(9) = 0.06667134;
			q.weights(8) = 0.14945134;
			q.weights(7) = 0.21908636;
			q.weights(6) = 0.26926672;
			q.weights(5) = 0.29552422;
			q.weights(4) = q.weights(5);
			q.weights(3) = q.weights(6);
			q.weights(2) = q.weights(7);
			q.weights(1) = q.weights(8);
			q.weights(0) = q.weights(9);

			return q;
		}

		default:
			throw NumLibError();
	}
}

}} //::numlib::integration
