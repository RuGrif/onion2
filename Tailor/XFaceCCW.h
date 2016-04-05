#pragma once


#include "../Collision/XPoint.h"
#include <map>


namespace Tailor_NS
{
  class XFaceCCW
  {
  public:
    
    XFaceCCW( Collision_NS::Vert );
    XFaceCCW( Collision_NS::Edge );
    XFaceCCW( Collision_NS::Face );

    bool operator()( const Collision_NS::XFace&, const Collision_NS::XFace& ) const;

  private:

    std::map<size_t, size_t> d_order; //  face id -> order
  };
}