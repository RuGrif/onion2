#pragma once


#include "GeoLocation.h"
#include "GeoLocationCCW.h"
#include "../Collision/XPoint.h"
#include "../QEdge/Shape.h"
#include <map>
#include <set>


namespace Tailor_NS
{
  class GeoGraph
  {
  public:

    using Edge = QEdge_NS::Edge;
    using XID = std::pair<size_t, size_t>;
    using EID = std::pair<size_t, size_t>;
    using Loc = std::pair<GeoLocation, GeoLocation>;

    struct GeoEdge;
    struct GeoVert;

  private:

    template <typename A, typename B>
    static std::pair<size_t, size_t> id( const std::pair<A, B>& p )
    {
      using Collision_NS::id;
      return{ id( p.first ), id( p.second ) };
    }


    template <typename A, typename B>
    static std::pair<B, A> castle( const std::pair<A, B>& p )
    {
      return{ p.second, p.first };
    }

  public:

    template <typename P0, typename E, typename P1>
    void operator() ( const P0& p0, const E& e, const P1& p1 )
    {
      EID eid = id( e );

      if( !( eid.first < eid.second ) ) return;  //  make only one half-edge of two

      add(
        id( p0 ), getGeoLocation( p0, e ),
        eid,
        id( p1 ), getGeoLocation( p1, e ) );
    }

  private:

    void add( const XID&, const Loc&, const EID&, const XID&, const Loc& );

  private:

    std::map<EID, GeoEdge>  d_edges;
    std::map<XID, GeoVert>  d_verts;
    QEdge_NS::Shape         d_graphA;
    QEdge_NS::Shape         d_graphB;
  };


  struct GeoGraph::GeoEdge
  {
    XID o, d;
  };


  struct GeoGraph::GeoVert
  {
    std::set<EID, GeoLocationCCW> d_edges;

    GeoVert( const Collision_NS::XVert& );
    GeoVert( const Collision_NS::XEdge& );
    GeoVert( const Collision_NS::XFace& );

  private:

    GeoVert( const GeoLocationCCW& ccw ) : d_edges{ ccw } {}
  };
}