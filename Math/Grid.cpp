#include "Grid.h"
#include <cmath>


namespace
{
  //  floor operation
  Math_NS::Vector3L::Type f2i( double x ) { return static_cast<Math_NS::Vector3L::Type>( x < 0 ? x - 0.5 : x + 0.5 ); };
  
  const Math_NS::Vector3L::Type maxbox = std::numeric_limits<Math_NS::Vector3L::Type>::max();
  const Math_NS::Vector3L::Type maxframe = f2i( std::cbrt( maxbox / 6.0 ) ) - 1;
}


Math_NS::Grid::Grid( const Box3D& i_box, const Vector3D& i_frame )
  : d_center( ( i_box.min + i_box.max ) / 2.0 )
  , d_scale(
      std::min( maxbox / ( i_box.max.x - i_box.min.x ), maxframe / i_frame.x ),
      std::min( maxbox / ( i_box.max.y - i_box.min.y ), maxframe / i_frame.y ),
      std::min( maxbox / ( i_box.max.z - i_box.min.z ), maxframe / i_frame.z ) )
{

}


Math_NS::Vector3L Math_NS::Grid::operator()( const Math_NS::Vector3D& p ) const
{
  return
  {
    f2i( d_scale.x * ( p.x - d_center.x ) ),
    f2i( d_scale.y * ( p.y - d_center.y ) ),
    f2i( d_scale.z * ( p.z - d_center.z ) )
  };
}
