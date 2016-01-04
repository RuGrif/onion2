#include "Log.h"
#include <iostream>


void Run_NS::TimeLog::log()
{
  std::chrono::system_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  std::cout << "Time = " << std::chrono::duration_cast<std::chrono::milliseconds>( t1 - t0 ).count() << " ms" << std::endl;
  t0 = t1;
}
