/*! \file OptimizerPSO.h
 *  \brief OptimizerPSO class template definition
 */

#ifndef OPTIMIZER_PSO_H
#define OPTIMIZER_PSO_H

#include "../base/random.h"
#include "../array/PointerArray.h"

#include "optimization_error_codes.h"
#include "Particle.h"
#include "MinimumND.h"

namespace numlib{ namespace optimization{

//! Multi-variate optimizer based on Particle Swarm Optimization (PSO)
/*!
 *	This optimizer implements the Particle Swarm Optimization (PSO)
 *	algorithm introduced by Eberhart and Kennedy. PSO is a zeroth
 *	order heuristic optimization algorithm. Like Genetic Algorithms (GA),
 *	and Simulated Annealing (SA), PSO is fundamentally a statistical 
 *	algorithm which, given the right choice of parameters, gives a
 *	strong likelyhood of finding a global minimum. PSO may be applied
 *	to multimodal and mixed continous-discrete optimization problems.
 *	The current implementation assumes continuous variables; however,
 *	it has been shown that rounding to the nearest integer gives
 *	reasonable results.
 *
 *	It is assumed that the design space is nominally contained in the
 *	unit d-cube. Particles will be allowed to leave this area, however,
 *	all initial partical positions will fall within these limits. The
 *	recommendation is that your cost function be scaled such that
 *	these assumptions hold.
 *
 *	In regards to a stopping criterion, the usual convention is to
 *	monitor the change in the estimated minimum cost and stop when
 *	this values falls below a user specified threshold. For this
 *	kind of algorithm, this criterion does can result in premature
 *	termination. A plot of the cost estimate versus iteration will
 *	show a monotone non-increasing graph with many plateaus. Unfortunately,
 *	a rigourous stopping criterion does not currently exist for PSO.
 *	An interesting observation is that the number of iterations between
 *	each incremental change if gbest seems to increase as the swarm
 *	converges toward the optimum; perhaps monitoring the number of
 *	iterations since last change in gbest would be a better stopping
 *	criterion?
 *
 *	\todo Find better container type for swarm - one with a proper iterator
 *	would be nice.
 *
 *	\todo Replace use of Minimum with a generic Swarm? This would give
 *	the user more flexibility in setting initial conditions and monitoring
 *	solution progress.
 */
template<class F, class V, class P=Particle<F, V> >
class OptimizerPSO
{
public:

	typedef F FunctionType;
	typedef V VectorType;
	typedef P ParticleType;
	typedef MinimumND<VectorType> Minimum;

	OptimizerPSO(Size dim, Size np, Real tol_=5.0E-3, Size max_count_=10, Size max_iter_=1000):
		swarm(np),gbest(NULL), tol(tol_), max_count(max_count_), max_iter(max_iter_)
	{
		for(Index i=0; i<np; ++i)
			swarm[i] = new ParticleType(dim, i);
		gbest = swarm[0]; /* default value */
	}

	~OptimizerPSO()
	{
		swarm.clear();
	}

	//! Returns the number of particles
	Size size() const {return swarm.size();}

	//! Returns const pointer to the ith particle
	const ParticleType* particle(Index i) const {return swarm[i];}

	//! Sets the inertial of each particle to common value
	void inertia(const Real w)
	{
		for(Index i=0; i<swarm.size(); ++i)
			swarm[i]->inertia(w);
	}

	//! Initializes particle positions and velocities in the design space
	ErrorCode newSequence(FunctionType& f, Minimum& min)
	{
		// Re-seed random number generator ...

		randomSeed();

		// Initialize particles...

		VectorType pos0(min.design().size());
		VectorType vel0(min.design().size());

		randomVector(vel0, -0.1, 0.1);
		swarm[0]->newSequence(min.cost(), min.design(), vel0);

		for(Index i=1; i<swarm.size(); ++i)
		{
			randomVector(pos0, -1.0, 1.0);
			randomVector(vel0, -0.1, 0.1);
			swarm[i]->newSequence(f(pos0), pos0, vel0);
		}

		// Find best...

		gbest = swarm[0];
		for(Index i=1; i<swarm.size(); ++i)
		{
			if(gbest->bestCost() > swarm[i]->bestCost())
				gbest = swarm[i];
		}

		// Set best...

		for(Index i=0; i<swarm.size(); ++i)
			swarm[i]->bestParticle(gbest);

		min.design( gbest->bestPosition(), gbest->bestCost() );

		return SUCCESS;
	}

	//! Advances the dynamics of the swarm one time level
	ErrorCode iter(FunctionType& f, Minimum& min)
	{
		// Advance swarm...

		for(Index i=0; i<swarm.size(); ++i)
			swarm[i]->iter(f);

		// Find best...

		gbest = swarm[0];
		for(Index i=1; i<swarm.size(); ++i)
		{
			if(gbest->bestCost() > swarm[i]->bestCost())
				gbest = swarm[i];
		}

		// Set best...

		for(Index i=0; i<swarm.size(); ++i)
			swarm[i]->bestParticle(gbest);

		// Update solution..

		min.design( gbest->bestPosition(), gbest->bestCost() );

		return SUCCESS;

	}

	ErrorCode minimize(FunctionType& f, Minimum& min)
	{


		ErrorCode code = newSequence(f, min);

		Index count(0);
		for(Index n=0; n<max_iter; ++n)
		{
			Real fopt = min.cost();

			code = iter(f, min);

			if(code!=SUCCESS) return code;

			Real delta_f = fopt - min.cost();

			ASSERT( !(delta_f < 0) );

			if(delta_f < tol) 
				count++;
			else
				count = 0;

			if(count > max_count)
			{
				min.design( gbest->bestPosition(), gbest->bestCost() );
				return SUCCESS;
			}

		}

		return EXCEEDED_MAX_ITER;

	}

private:

	DISALLOW_COPY_AND_ASSIGN( OptimizerPSO );

	typedef array::PointerArray<ParticleType> Swarm;

	Swarm swarm;

	const ParticleType* gbest;

	Real tol;

	Size max_count;

	Size max_iter;

};

}}//::numlib::optimization

#endif
