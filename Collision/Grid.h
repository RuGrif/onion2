#pragma once


#include "..\Math\Vector3.h"


namespace Collision_NS
{
  class Grid
  {
  public:

    using Vec = Math_NS::Vector3L;
    using Int = Vec::Type;

    Math_NS::Vector3L operator() ( const Math_NS::Vector3D& ) const;
    Math_NS::Vector3D operator() ( const Math_NS::Vector3L& ) const;
  };
}