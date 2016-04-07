#include "Splice.h"


void Tailor_NS::Splice::operator()( Edge e, const XFace& f, const XPointID& xid )
{
  if( d_cached )
  {
    switch( d_cache.size() )
    {
    case 1:
      e.splice0( d_cache.front().second );
      //  fall thru
    case 0:
      d_cache.emplace_back( std::make_pair( f, xid ), e );
      return; //  exit

    default:
      d_edges.insert( d_cache.begin(), d_cache.end() );
      d_cached = false;
    }
  }
  
  if( !d_cached )
  {
    e.splice0( insert( e, f, xid ) );
  }
}


QEdge_NS::Edge Tailor_NS::Splice::insert( Edge e, const XFace& f, const XPointID& xid )
{
  //  find edge right after input one
  auto x = d_edges.emplace( std::piecewise_construct, std::forward_as_tuple( f, xid ), std::forward_as_tuple( e ) );
  auto i = x.first;

  //  take previous edge
  i = ( i == d_edges.begin() ) ? std::prev( d_edges.end() ) : std::prev( i );

  return i->second;
}


QEdge_NS::Edge Tailor_NS::Splice::edge() const
{
  return d_cache.empty() ? QEdge_NS::Edge{} : d_cache.front().second;
}