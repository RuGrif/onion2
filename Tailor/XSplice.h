#pragma once


#include "Segment.h"
#include "Data.h"
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
    void saveVert( const A& a, const B& b )
    {
      resetXPointData( d_vert, a, b );
    }

    void splice()
    {
      if( !d_edges.empty() )
      {
        for( auto i = std::next( d_edges.begin() ); i != d_edges.end(); ++i )
        {
          i->second.splice0( std::prev( i )->second );
        }
      }
    }

    void setVert()
    {
      if( !d_edges.empty() )
      {
        d_edges.begin()->second.o().swap( d_vert );
      }
    }

  private:

    std::map<Segment, QEdge_NS::Edge> d_edges;
    QEdge_NS::Vert                    d_vert;
  };
}