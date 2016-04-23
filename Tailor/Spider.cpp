#include "Spider.h"
#include "XSplice.h"


QEdge_NS::Edge Tailor_NS::Web::getOrCreateEdge( const Collision_NS::XPointID& id0, const Collision_NS::XPointID& id1 )
{
  auto f = d_edges.find( { id1, id0 } );  //  look for existing sym edge

  if( f != d_edges.end() )
  {
    QEdge_NS::Edge e = f->second.sym();
    d_edges.erase( f );
    return e;
  }
  else
  {
    return d_edges[ { id0, id1 } ] = d_web.makeEdge();
  }
}


namespace Tailor_NS
{
  template <typename P>
  void feed( XSplice&, const P&, const TwinEdgeCollection&, const Collision_NS::XPointID& )
  {
    //  empty
  }


  template <>
  void feed(
    XSplice& xsplice,
    const Collision_NS::XEdge& e,
    const TwinEdgeCollection& collection,
    const Collision_NS::XPointID& xid )
  {
    auto edges = collection.twinEdge( id( e ) ).edgePair( xid );
    xsplice( edges.first,  Segment( Collision_NS::Edge{ e.e().sym() } ) );
    xsplice( edges.second, Segment( Collision_NS::Edge{ e.e() } ) );
  };
}


Tailor_NS::DeferSplice Tailor_NS::Spider::spin( const TopoGraph& g, const Doppelganger& twin )
{
  DeferSplice defer;

  g.forEachXPoint( [&]( const auto& p0 )
  {
    XSplice xA;
    XSplice xB;

    xA.saveVert( p0.first, p0.second );
    xB.saveVert( p0.second, p0.first );

    auto xidA = []( const auto& p ) { return makeXPointID( p.first, p.second ); };
    auto xidB = []( const auto& p ) { return makeXPointID( p.second, p.first ); };

    auto xidA0 = xidA( p0 );
    auto xidB0 = xidB( p0 );

    g.forEachXEdge( p0, [&]( const auto&, const auto& e, const auto& p1 )
    {
      auto xidA1 = xidA( p1 );
      auto xidB1 = xidB( p1 );

      QEdge_NS::Edge eA = d_webA.getOrCreateEdge( xidA0, xidA1 );
      QEdge_NS::Edge eB = d_webB.getOrCreateEdge( xidB0, xidB1 );

      Segment sA{ p0.first,  e.first.e(),  p1.first,  Collision_NS::makeXSegmentID( e.first, e.second ) };
      Segment sB{ p0.second, e.second.e(), p1.second, Collision_NS::makeXSegmentID( e.second, e.first ) };

      xA( eA, std::move( sA ) );
      xB( eB, std::move( sB ) );
    } );

    feed( xA, p0.first,  twin.getDoppelgangerA(), xidA0 );
    feed( xB, p0.second, twin.getDoppelgangerB(), xidB0 );

    defer.spliceOrDefer( std::move( xA ), p0.first );
    defer.spliceOrDefer( std::move( xB ), p0.second );
  } );

  return defer;
}