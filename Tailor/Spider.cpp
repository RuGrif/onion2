#include "Spider.h"
//#include "XSplice.h"
#include "Splice.h"
#include "Data.h"


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


void Tailor_NS::Spider::spin( const Graph& g )
{
  g.forEachXPoint( [&]( const auto& p0 )
  {
    using A = std::remove_cv_t<decltype( p0.first )>;
    using B = std::remove_cv_t<decltype( p0.second )>;

    //XSplice<A> xA{ p0.first };
    //XSplice<B> xB{ p0.second };
    Splice xA{ p0.first };
    Splice xB{ p0.second };

    auto xidA = []( const auto& p ) { return makeXPointID( p.first, p.second ); };
    auto xidB = []( const auto& p ) { return makeXPointID( p.second, p.first ); };

    auto xidA0 = xidA( p0 );
    auto xidB0 = xidB( p0 );

    g.forEachXEdge( p0, [&]( const auto&, const auto& p1 )
    {
      auto xidA1 = xidA( p1 );
      auto xidB1 = xidB( p1 );

      QEdge_NS::Edge eA = d_webA.getOrCreateEdge( xidA0, xidA1 );
      QEdge_NS::Edge eB = d_webB.getOrCreateEdge( xidB0, xidB1 );

      xA( eA, p1.first, xidA1 );
      xB( eB, p1.second, xidB1 );

      setXPointData( eA.sym(), p1.first, p1.second );
      setXPointData( eB.sym(), p1.second, p1.first );
    } );

    if( xA.edge() ) setXPointData( xA.edge(), p0.first, p0.second );
    if( xB.edge() ) setXPointData( xB.edge(), p0.second, p0.first );
  } );
}