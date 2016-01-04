#include <chrono>


namespace Run_NS
{
  class TimeLog
  {
    std::chrono::system_clock::time_point t0 = std::chrono::high_resolution_clock::now();
  public:
    void log();
  };
}