#include "Grid.h"
#include <cmath>


namespace
{
  //  floor operation
  Math_NS::Vector3L::Type f2i( double x ) { return static_cast<Math_NS::Vector3L::Type>( ::floor( x ) ); };
  
  //  solving 3-dim equation within the frame wouldn't lead to overflow
  //  see solve() method
  //const Math_NS::Vector3L::Type maxframe = f2i( std::cbrt( std::numeric_limits<Math_NS::Vector3L::Type>::max() / 6.0 ) ) - 1;
}


Math_NS::Vector3L Math_NS::Grid::operator()( const Math_NS::Vector3D& p ) const
{
  return
  {
    f2i( d_scale.x * p.x ),
    f2i( d_scale.y * p.y ),
    f2i( d_scale.z * p.z )
  };
}
