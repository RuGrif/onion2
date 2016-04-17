#pragma once


#include "FaceCCW.h"
#include "BaryCCW.h"
#include "../Collision/XPoint.h"
#include <map>


namespace Tailor_NS
{
  //  counter clockwise intersection edge comparison predicate
  class XEdgeCCW
  {
  public:

    XEdgeCCW( const Collision_NS::XVert& ); //  path intersection vertex on vertex as rotation center
    XEdgeCCW( const Collision_NS::XEdge& ); //  path intersection vertex on edge as rotation center
    XEdgeCCW( const Collision_NS::XFace& ); //  path intersection vertex on face as rotation center

    bool operator() ( const Collision_NS::XFace& l, const Collision_NS::XFace& r ) const;

  private:

    FaceCCW                     d_faceCCW;
    std::map<size_t, BaryCCW>   d_baryCCW;  //  face id -> on-face sorter
  };
}