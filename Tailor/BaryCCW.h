#pragma once


#include "../Collision/Barycentric.h"


namespace Tailor_NS
{
  //  ccw points comparison with rotation center in point O
  class BaryCCW
  {
  public:

    using BaryF = Collision_NS::BaryF;

    BaryCCW( const BaryF& o ) : o{ o } {}

    bool operator()( const BaryF&, const BaryF& ) const;

  private:

    BaryF o;  //  rotation center
  };
}