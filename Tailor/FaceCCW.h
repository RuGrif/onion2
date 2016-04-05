#pragma once


#include "../Collision/Primitive.h"
#include <map>


namespace Tailor_NS
{
  class FaceCCW
  {
  public:
    
    FaceCCW( Collision_NS::Vert );
    FaceCCW( Collision_NS::Edge );
    FaceCCW( Collision_NS::Face );

    bool operator()( const Collision_NS::Face&, const Collision_NS::Face& ) const;

  private:

    std::map<size_t, size_t> d_order; //  face id -> order
  };
}