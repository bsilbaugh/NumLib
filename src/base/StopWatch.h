/*! \file StopWatch
 */

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>

#include "numlib-config.h"

namespace numlib{

//! A class for timing algorithms
class StopWatch
{
public:

	StopWatch():total(0.0){}

	void start() { lap_time = std::clock(); }

	Real stop() 
	{
		// Compute elapsed time in ticks...
		lap_time = clock() - lap_time;

		// Compute total elasped time...
		total += (Real)lap_time/CLOCKS_PER_SEC;

		// Return elaspsed time in seconds...
		return total;
	}

	void reset() { total = 0.0; }

private:

	std::clock_t lap_time;
	Real total;

};

}//::numlib

#endif
