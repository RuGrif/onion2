#include "Spider.h"
#include "XSplice.h"
#include <list>


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


void Tailor_NS::Spider::spin( const TopoGraph& g )
{
  std::list<XSplice> deferredSplice;

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

      Collision_NS::Face fA{ e.first.e() };
      Collision_NS::Face fB{ e.second.e() };

      xA( eA, p0.first,  fA, p1.first,  Collision_NS::makeXSegmentID( e.first, e.second ) );
      xB( eB, p0.second, fB, p1.second, Collision_NS::makeXSegmentID( e.second, e.first ) );
    } );

    deferredSplice.emplace_back( std::move( xA ) );
    deferredSplice.emplace_back( std::move( xB ) );
  } );

  std::for_each( deferredSplice.begin(), deferredSplice.end(), std::mem_fn( &XSplice::splice ) );
  std::for_each( deferredSplice.begin(), deferredSplice.end(), std::mem_fn( &XSplice::setVert ) );
}