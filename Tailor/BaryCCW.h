#pragma once


#include "../Collision/Barycentric.h"


namespace Tailor_NS
{
  //  counter clockwise points comparison predicate
  //  points are on same face
  //  points position are given in barycentric coordinates
  //  rotation center is O
  class BaryCCW
  {
  public:

    using BaryF = Collision_NS::BaryF;

    BaryCCW( const BaryF& o ) : o{ o } {} //  pass rotation center

    bool operator()( const BaryF&, const BaryF& ) const;

  private:

    BaryF o;  //  rotation center
  };
}