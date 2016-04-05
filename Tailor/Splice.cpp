#include "Splice.h"


void Tailor_NS::Splice::operator()( Edge e, const XFace& f, const XPointID& xid )
{
  if( d_cached )
  {
    if( d_cache.size() < 2 )
    {
      d_cache.emplace_back( std::make_pair( f, xid ), e );
    }
    else
    {
      d_cached = false;
      d_edges.insert( d_cache.begin(), d_cache.end() );
      insert( e, f, xid );
    }
  }
  else
  {
    insert( e, f, xid );
  }
}


void Tailor_NS::Splice::insert( Edge e, const XFace& f, const XPointID& xid )
{
  //  find edge right after input one
  auto x = d_edges.emplace( std::piecewise_construct, std::forward_as_tuple( f, xid ), std::forward_as_tuple( e ) );
  auto i = x.first;

  //  take previous edge
  i = ( i == d_edges.begin() ) ? std::prev( d_edges.end() ) : std::prev( i );

  //  splice
  e.splice0( i->second );
}


QEdge_NS::Edge Tailor_NS::Splice::edge() const
{
  return d_cache.empty() ? QEdge_NS::Edge{} : d_cache.front().second;
}