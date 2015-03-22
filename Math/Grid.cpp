#include "Grid.h"
#include <cmath>


namespace
{
  //  floor operation
  Math_NS::Vector3L::Type f2i( double x ) { return static_cast<Math_NS::Vector3L::Type>( x < 0 ? x - 0.5 : x + 0.5 ); };
  
  //  solving 3-dim equation within the frame wouldn't lead to overflow
  //  see solve() method
  const Math_NS::Vector3L::Type maxframe = f2i( std::cbrt( std::numeric_limits<Math_NS::Vector3L::Type>::max() / 6.0 ) ) - 1;
}


Math_NS::Grid::Grid( const Vector3D& i_frame )
  //: d_scale( maxframe / i_frame.x, maxframe / i_frame.y, maxframe / i_frame.z )
  : d_scale( 1 << 12, 1 << 12, 1 << 12 )
{

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
