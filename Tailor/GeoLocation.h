#pragma once


#include "../Collision/XPoint.h"


namespace Tailor_NS
{
  struct GeoLocation
  {
    using Face = Collision_NS::Face;
    using Bary = Collision_NS::BaryF;
    using XID = Collision_NS::XPointID;

    Face      d_face;
    Bary      d_bary;
    XID       d_xid;
  };


  inline Collision_NS::Face getFace( Collision_NS::Face f ) { return f; }
  inline Collision_NS::Face getFace( Collision_NS::Edge e ) { return e.isMajor() ? e.e() : e.e().sym(); }
  
  Collision_NS::Face getFace( Collision_NS::Vert v );


  //  compute intersection point geo-location on the shape based on intersection vertex topo-location and intersection edge topo-location
  template <typename XVert, typename XEdge>
  GeoLocation getGeoLocation( const XVert& i_xvert, XEdge i_xedge, const Collision_NS::XPointID& i_xid )
  {
    Collision_NS::Face face = getFace( i_xedge );
    return
    {
      face,
      i_xvert.toXFace( face ),
      i_xid
    };
  }


  template <typename A, typename B, typename EA, typename EB>
  std::pair<GeoLocation, GeoLocation> getGeoLocation( const Collision_NS::XPoint<A, B>& i_point, const std::pair<EA, EB>& i_edge )
  {
    return
    {
      getGeoLocation( i_point.first, i_edge.first, makeXPointID( i_point.first, i_point.second ) ),
      getGeoLocation( i_point.second, i_edge.second, makeXPointID( i_point.second, i_point.first ) )
    };
  }
}