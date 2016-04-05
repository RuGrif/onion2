#pragma once


#include "../Collision/Barycentric.h"


namespace Tailor_NS
{
  //  ccw points comparison with rotation center in point O
  struct FaceCCW
  {
    using Point = Collision_NS::BaryF;

    Point o;  //  rotation center

    bool operator()( const Point&, const Point& ) const;
  };
}