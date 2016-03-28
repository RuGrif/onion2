#include "Graph.h"


void Collision_NS::Graph::add( const XVert& x, const XVert& y, bool a ) { makeXPoint( x, y, a ); }
void Collision_NS::Graph::add( const XVert& x, const XEdge& y, bool a ) { makeXPoint( x, y, a ); }
void Collision_NS::Graph::add( const XVert& x, const XFace& y, bool a ) { makeXPoint( x, y, a ); }
void Collision_NS::Graph::add( const XEdge& x, const XEdge& y, bool a ) { makeXPoint( x, y, a ); }
void Collision_NS::Graph::add( const XEdge& x, const XFace& y, bool a ) { makeXPoint( x, y, a ); }


template <typename A, typename B>
void Collision_NS::Graph::makeXPoint( const A& a, const B& b, bool alter )
{
  if( alter )
  {
    makeXPoint( b, a );
  }
  else
  {
    makeXPoint( a, b );
  }
}


template <typename A, typename B>
void Collision_NS::Graph::makeXPoint( const A& a, const B& b )
{
  XVertID x{ id( a ), id( b ) };  //  this XPoint

  if( d_xpoints.find( x ) == d_xpoints.end() )
  {
    QEdge_NS::Edge e = d_graph.makeLoop();

    e.o().reset<XPoint<A, B>>( a, b );

    YVertID y{ a, b, e };           //  potential neighbor XPoints

    connect( x, y );

    d_xpoints.emplace( std::move( x ), std::move( y ) );
  }
}


void Collision_NS::Graph::connect( const XVertID& x, const YVertID& y )
{
  for( size_t ia : y.alpha ) for( size_t ib : y.beta )
  {
    XVertID i{ ia, ib };

    if( i != x )
    {
      auto f = d_xpoints.find( i );

      //  if neighbor XPoint found
      if( f != d_xpoints.end() )
      {
        QEdge_NS::Edge e = d_graph.makeEdge();  //  connection edge
        QEdge_NS::Edge v0 = y.edge;             //  me, new XPoint
        QEdge_NS::Edge v1 = f->second.edge;     //  neighbor XPoint
        v0.splice0( e );
        v1.splice0( e.sym() );
      }
    }
  }
}