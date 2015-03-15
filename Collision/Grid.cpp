#include "Grid.h"


Math_NS::Vector3L Collision_NS::Grid::operator() ( const Math_NS::Vector3D& v ) const
{
  const double s = 1000;
  return
  {
    static_cast<Math_NS::Vector3L::Type>( s * v.x ),
    static_cast<Math_NS::Vector3L::Type>( s * v.y ),
    static_cast<Math_NS::Vector3L::Type>( s * v.z )
  };
}
