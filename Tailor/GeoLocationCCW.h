#pragma once


#include "FaceCCW.h"
#include "BaryCCW.h"
#include "GeoLocation.h"
#include <map>


namespace Tailor_NS
{
  //  counter clockwise intersection edge comparison predicate
  class GeoLocationCCW
  {
  public:

    GeoLocationCCW( const Collision_NS::XVert& ); //  path intersection vertex on vertex as rotation center
    GeoLocationCCW( const Collision_NS::XEdge& ); //  path intersection vertex on edge as rotation center
    GeoLocationCCW( const Collision_NS::XFace& ); //  path intersection vertex on face as rotation center

    bool operator() ( const GeoLocation& l, const GeoLocation& r ) const;

  private:

    FaceCCW                     d_faceCCW;
    std::map<size_t, BaryCCW>   d_baryCCW;  //  face id -> on-face sorter
  };
}