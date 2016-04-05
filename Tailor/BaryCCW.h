#pragma once


#include "../Collision/Barycentric.h"


namespace Tailor_NS
{
  //  ccw points comparison with rotation center in point O
  struct BaryCCW
  {
    using BaryF = Collision_NS::BaryF;

    BaryF o;  //  rotation center

    bool operator()( const BaryF&, const BaryF& ) const;
  };
}