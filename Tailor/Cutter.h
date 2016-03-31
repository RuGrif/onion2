#pragma once


#include "../QEdge/Shape.h"
#include "../Collision/Intersection.h"
#include "Graph.h"
#include "Data.h"
#include <map>
#include "Tailor.h"


namespace Tailor_NS
{
  //  manage all intersection edges for one shape
  class Web
  {
  public:

    using XVertID = Collision_NS::XPointID;
    using XEdgeID = std::pair<XVertID, XVertID>;

    QEdge_NS::Edge getOrCreateEdge( const Collision_NS::XPointID& id0, const Collision_NS::XPointID& id1 )
    {
      auto f = d_edges.find( { id1, id0 } );  //  look for existing sym edge
      
      if( f != d_edges.end() )
      {
        return f->second.sym();
      }
      else
      {
        return d_edges[ { id0, id0 } ] = d_graph.makeEdge();
      }
    }

  private:

    std::map<XEdgeID, QEdge_NS::Edge>   d_edges;
    QEdge_NS::Shape                     d_graph;
  };


  //  manage intersection edges stitching for one vertex for one shape
  template <typename A0, typename B0>
  struct Spider
  {
    using X0 = Collision_NS::XPoint<A0, B0>;

    Web&        web;
    const X0&   p0;    

    template <typename A1, typename B1>
    void operator() ( const Collision_NS::XPoint<A0, B0>&, const Collision_NS::XPoint<A1, B1>& p1 )
    {
      QEdge_NS::Edge e = web.getOrCreateEdge( makeXPointId( p0.first, p0.second ), makeXPointID( p1.first, p1.second ) );

      if( e.oNext() != e )
      {
        throw std::logic_error( "Not implemented yet" );
      }

      if( o ) e.splice0( o );

      o = e;
    }

    void setVertData() { if( o ) Tailor_NS::setXPointData( o, p0.first, p0.second ); }

  private:

    QEdge_NS::Edge o;
  };


  class Tailor
  {
  public:

    void tail( const Graph& g )
    {
      using V = Graph::V;
      using E = Graph::E;
      using F = Graph::F;

      tail<V, V>( g );
      tail<V, E>( g );
      tail<V, F>( g );

      tail<E, V>( g );
      tail<E, E>( g );
      tail<E, F>( g );

      tail<F, V>( g );
      tail<F, E>( g );
    }

  private:

    template <typename A, typename B>
    void tail( const Graph& g )
    {
      for( const auto& p0 : g.collection().get<A, B>() )
      {
        g.forEachXEdge<A, B>( p0.second, Spider<A, B>{ webA, p0.second } );
        g.forEachXEdge<A, B>( p0.second, Spider<A, B>{ webB, p0.second } ); //  speedup
      }
    }

  private:

    Web webA, webB;
  };
}