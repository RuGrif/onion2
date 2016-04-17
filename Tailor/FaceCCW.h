#pragma once


#include "../Collision/Primitive.h"
#include <map>


namespace Tailor_NS
{
  //  counter clockwise face comparison predicate
  //  face are around same vertex or edge
  //  support degenerated case: rotation around the face
  class FaceCCW
  {
  public:
    
    FaceCCW( Collision_NS::Vert );  //  path vertex as rotation center
    FaceCCW( Collision_NS::Edge );  //  path edge as rotation center
    FaceCCW( Collision_NS::Face );  //  path face as degenerated rotation center

    bool operator()( const Collision_NS::Face&, const Collision_NS::Face& ) const;

  private:

    std::map<size_t, size_t> d_order; //  face id -> order
  };
}