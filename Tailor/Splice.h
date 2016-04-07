#pragma once


#include "XEdgeCCW.h"
#include "../QEdge/Edge.h"


namespace Tailor_NS
{
  //  self-intersection support for intersection edges counter clock wise sorting predicate
  struct XEdgeSICCW : public XEdgeCCW
  {
    using XFace     = Collision_NS::XFace;
    using XPointID  = Collision_NS::XPointID;
    using XFaceSI   = std::pair<XFace, XPointID>;

    template <typename P> XEdgeSICCW( const P& p ) : XEdgeCCW{ p } {}

    bool operator() ( const XFaceSI& l, const XFaceSI& r ) const
    {
      //  ( l.f < r.f ) || ( ( l.f == r.f ) && ( l.s < r.s ) )
      //  ( l.f < r.f ) || ( !( r.f < l.f ) && ( l.s < r.s ) )
      return XEdgeCCW::operator()( l.first, r.first ) || ( !XEdgeCCW::operator()( r.first, l.first ) && ( l.second < r.second ) );
    }
  };


  class Splice
  {
  public:

    using XFace       = Collision_NS::XFace;
    using XPointID    = Collision_NS::XPointID;
    using Edge        = QEdge_NS::Edge;

    template <typename P> Splice( const P& p ) : d_edges{ XEdgeSICCW{ p } } { d_cache.reserve( 2 ); }

    void operator()( Edge, const XFace&, const XPointID& );

    Edge edge() const;

  private:

    Edge insert( Edge, const XFace&, const XPointID& );

  private:
    
    using XFaceSI = std::pair<XFace, XPointID>;

    std::map<XFaceSI, Edge, XEdgeSICCW>       d_edges;
    std::vector<std::pair<XFaceSI, Edge>>     d_cache;
    bool                                      d_cached = true;
  };
}