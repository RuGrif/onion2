#include "Grid.h"
#include <cmath>
#include <cinttypes>


namespace
{
  //  float to integer
  Math_NS::Vector3L::Type f2i( double x ) { return static_cast<Math_NS::Vector3L::Type>( ::round( x ) ); };
  const double scale = 1024;// std::numeric_limits<std::uint32_t>::max();
}


Math_NS::Vector3L Math_NS::Grid::operator()( const Math_NS::Vector3D& p ) const
{
  return
  {
    f2i( ( p.x - d_box.min.x ) / ( d_box.max.x - d_box.min.x ) * scale ),
    f2i( ( p.y - d_box.min.y ) / ( d_box.max.y - d_box.min.y ) * scale ),
    f2i( ( p.z - d_box.min.z ) / ( d_box.max.z - d_box.min.z ) * scale ),
  };
}
