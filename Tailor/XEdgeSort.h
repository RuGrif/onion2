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

    bool operator() ( const Collision_NS::XFace& l, const Collision_NS::XFace& r ) const
    {
      return id( l ) == id( r ) ? d_baryCCW.at( id( l ) )( l, r ) : d_faceCCW( l, r );
    }

  private:

    FaceCCW                     d_faceCCW;
    std::map<size_t, BaryCCW>   d_baryCCW;
  };
}