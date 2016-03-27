#include "Grid.h"
#include <cmath>
#include <cinttypes>


namespace
{
  //  float to integer
  //  expect -1 <= x <= 1
  Math_NS::Vector3L::Type f2i( double x ) { return ::llround( x * std::numeric_limits<std::int32_t>::max() ); };
}


Math_NS::Grid::Grid( const Math_NS::Box3D& i_box )
  : d_zero( ( i_box.min + i_box.max ) / 2. )
  , d_diag( ( i_box.max - i_box.min ) / 2. )
{}


Math_NS::Vector3L Math_NS::Grid::operator()( const Math_NS::Vector3D& p ) const
{
  return
  {
    f2i( ( p.x - d_zero.x ) / d_diag.x ),
    f2i( ( p.y - d_zero.y ) / d_diag.y ),
    f2i( ( p.z - d_zero.z ) / d_diag.z ),
  };
}
