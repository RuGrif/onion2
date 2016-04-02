#pragma once


#include "../Math/Vector3.h"


namespace Collision_NS
{
  struct BaryV
  {
    using Int = Math_NS::Vector3L::Type;
    //  empty
  };

  struct BaryE
  {
    using Int = Math_NS::Vector3L::Type;

    Int u, v;
  };


  struct BaryF
  {
    using Int = Math_NS::Vector3L::Type;

    Int a, b, c;
  };
}