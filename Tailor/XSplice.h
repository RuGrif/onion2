#pragma once


#include "Segment.h"
#include "../Collision/XPoint.h"


namespace Tailor_NS
{
  class XSplice
  {
  public:

    template <typename P0, typename P1>
    void operator() ( QEdge_NS::Edge e, const P0& p0, Collision_NS::Face f, const P1& p1, const Collision_NS::XSegmentID& sid )
    {
      d_edges.emplace( std::piecewise_construct, std::forward_as_tuple( p0, f, p1, sid ), std::forward_as_tuple( e ) );
    }

    template <typename A, typename B>
    void splice( const A& a, const B& b )
    {
      if( d_edges.empty() ) return;
      
      for( auto i = std::next( d_edges.begin() ); i != d_edges.end(); ++i )
      {
        i->second.splice0( std::prev( i ) ->second );
      }

      setXPointData( d_edges.begin()->second, a, b );
    }

  private:

    std::map<Segment, QEdge_NS::Edge> d_edges;
  };
}