#include "Grid.h"


Math_NS::Vector3L Collision_NS::Grid::operator() ( const Math_NS::Vector3D& v ) const
{
  return
  {
    static_cast<Math_NS::Vector3L::Type>( v.x ),
    static_cast<Math_NS::Vector3L::Type>( v.y ),
    static_cast<Math_NS::Vector3L::Type>( v.z )
  };
}


Math_NS::Vector3D Collision_NS::Grid::operator() ( const Math_NS::Vector3L& v ) const
{
  return
  {
    static_cast<Math_NS::Vector3D::Type>( v.x ),
    static_cast<Math_NS::Vector3D::Type>( v.y ),
    static_cast<Math_NS::Vector3D::Type>( v.z )
  };
}