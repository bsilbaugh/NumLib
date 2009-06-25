/*! \file ScopedTimer.h
 */

#ifndef SCOPEDTIMER_H
#define SCOPEDTIMER_H

#include <iostream>

namespace numlib{

class ScopedTimer
{
public:

  ScopedTimer()
  {
	epoch = std::clock();
  }

  ~ScopedTimer()
  {
	epoch = std::clock() - epoch;
	std::cout<<"Elapsed time (sec) = "<<(Real)epoch/CLOCKS_PER_SEC<<std::endl;
  }

private:

  std::clock_t epoch;

};

}//::numlib

#endif
