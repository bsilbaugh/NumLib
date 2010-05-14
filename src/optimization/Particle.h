/*! \file Particle.h
 *  \brief Particle class template definition
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include "../base/random.h"

namespace numlib{ namespace optimization{

//! Model of a basic ``particle'' used in Particle Swarm Optimization (PSO)
/*!
 *  The dynamics of this particle are based on the standard particle model
 *  defined by Kenney and Eberhart. However, more sophisticated dynamic
 *  models could be contrived. Alternative particle classes may be used
 *  with OptimizerPSO provided that these alternative particle classes
 *  implement the interface defined here.
 *
 */
template<class F, class V>
class Particle
{
public:

	typedef F FunctionType;
	typedef V VectorType;

	Particle(Size dim, Index id_):
		id(id_),
		vmax(0.5),
		w(1.0), c1(1.5), c2(2.5),
		cst(0), pos(dim), vel(dim),
		pbest_cst(0), pbest_pos(dim),
		gbest(NULL)
	{}

	Particle(const Particle& other):
		w(other.w), c1(other.c1), c2(other.c2), 
		cst(other.cst), pos(other.pos), vel(other.vel), 
		pbest_cst(other.pbest_cst), pbest_pos(other.pbest_pos),
		gbest(other.gbest)
	{}

	Particle operator=(const Particle& other)
	{
		if(this==&other) return *this;

		w = other.w;
		c1 = other.c1;
		c2 = other.c2;
		cst = other.cst;
		pos = other.pos;
		vel = other.vel;
		pbest_cst = other.pbest_cst;
		pbest_pos = other.pbest_pos;
		gbest = other.gbest;

		return *this;
	}

	~Particle()
	{
		/* all data auto delete */
	}

	void maxVelocity(Real vmax_) {vmax = vmax_;}

	//! Sets particle ``inertia''
	/*!
	 *	This parameters was introduced by Eberhart and Kennedy
	 *	to mitigate the convergence to local minima. Choosing
	 *	a large value results in a more global exploration of
	 *	the design space but may hinder convergence to a minima.
	 *	Choosing a small value results in a more local exploration
	 *	of the design space but may cause the swarm to get trapped
	 *	into a local minima. Numerical experiments would suggest
	 *	that the decreasing the inertia from a large value (e.g. 1.2) 
	 *	to zero over the duration of the simulation yeilds good results.
	 *
	 *	If alternative globalization techniques are used, such as function
	 *	stretching, then in princple this parameter could be set to zero.
	 */
	void inertia(Real w_) {w = w_;}

	void selfTrust(Real c1_) {c1 = c1_;}

	void swarmTrust(Real c2_) {c2 = c2_;}

	const Real maxVelocity() const {return vmax;}

	const Real inertia() const {return w;}

	const Real confidence() const {return c1;}

	const Real trust() const {return c2;}
	
	const VectorType& bestPosition() const {return pbest_pos;}

	const Real bestCost() const {return pbest_cst;}

	const VectorType& position() const {return pos;}

	const VectorType& velocity() const {return vel;}

	const Real& cost() const {return cst;}

	void newSequence(FunctionType& f)
	{
		// Set initial position and velocity...

		ASSERT( vel.size() == pos.size() );

		Size dim = pos.size();

		//randomSeed();

		for(Index i=0; i<dim; ++i)
		{
			pos(i) = 2.0*randomNumber() - 1.0;
			vel(i) = 2.0*randomNumber() - 1.0;
		}

		constrictionOperator(vel);

		// Compute cost at initial position...

		cst = f(pos);

		// Set pbest to initial position and cost...

		pbest_pos = pos;
		pbest_cst = cst;

		// Initialize gbest to self...

		gbest = this;

	}

	void bestParticle(const Particle* gbest_) {gbest = gbest_;}

	void iter(FunctionType& f)
	{
		// Update velocity...

		Real r1 = randomNumber();
		Real r2 = randomNumber();

		vel *= w;
		vel += c1*r1*(pbest_pos - pos);
		vel += c2*r2*(gbest->bestPosition() - pos);

		constrictionOperator(vel);

		// Update position...
		
		pos += vel;

		// Update cost...

		cst = f(pos);

		// Update personal best...

		if(cst < pbest_cst)
		{
			pbest_cst = cst;
			pbest_pos = pos;
		}
	}

private:

	Index id;

	Real vmax;

	Real w, c1, c2;

	Real cst;

	VectorType pos;

	VectorType vel;

	Real pbest_cst;

	VectorType pbest_pos;

	const Particle* gbest;

	void constrictionOperator(VectorType& u)
	{
		Real umag = norm2(u);
		if(umag > vmax)
			u *= vmax/umag;
	}

};

}}//::numlib::optimization

#endif
