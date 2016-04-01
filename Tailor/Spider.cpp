#include "Spider.h"
#include "XSplice.h"


void Tailor_NS::Spider::spin( const Graph& g )
{
  g.forEachXPoint( [&]( const auto& p0 )
  {
    using A = std::remove_cv_t<decltype( p0.first )>;
    using B = std::remove_cv_t<decltype( p0.second )>;

    XSplice<A> xA{ p0.first };
    XSplice<B> xB{ p0.second };

    auto xidA = []( const auto& p ) { return makeXPointID( p.first, p.second ); };
    auto xidB = []( const auto& p ) { return makeXPointID( p.second, p.first ); };

    g.forEachXEdge( p0, [&]( const auto&, const auto& p1 )
    {
      QEdge_NS::Edge eA = webA.getOrCreateEdge( xidA( p0 ), xidA( p1 ) );
      QEdge_NS::Edge eB = webB.getOrCreateEdge( xidB( p0 ), xidB( p1 ) );

      xA( eA, p1.first );
      xB( eB, p1.second );
    } );
  } );
}