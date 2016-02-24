#include <chrono>


namespace Run_NS
{
  class TimeLog
  {
    std::chrono::time_point<std::chrono::high_resolution_clock> t0 = std::chrono::high_resolution_clock::now();
  public:
    void log();
  };
}