#pragma once


#include "FaceCCW.h"
#include "BaryCCW.h"
#include "../Collision/XPoint.h"
#include <map>


namespace Tailor_NS
{
  class XEdgeCCW
  {
  public:

    XEdgeCCW( const Collision_NS::XVert& );
    XEdgeCCW( const Collision_NS::XEdge& );
    XEdgeCCW( const Collision_NS::XFace& );

    bool operator() ( const Collision_NS::XFace& l, const Collision_NS::XFace& r ) const;

  private:

    FaceCCW                     d_faceCCW;
    std::map<size_t, BaryCCW>   d_baryCCW;
  };
}