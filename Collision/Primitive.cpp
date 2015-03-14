#include "Primitive.h"


Collision_NS::Prim::Neighborhood Collision_NS::Vert::neighbourhood() const
{
  Neighborhood nb;

  nb.push_back( Vert( d_edge ) );

  QEdge_NS::Edge e = d_edge;
  do
  {
    nb.push_back( Edge( e ) );
    nb.push_back( Vert( e.sym() ) );
    nb.push_back( Face( e ) );
    nb.push_back( Edge( e.lNext() ) );
    e = e.oNext();
  }
  while( e != d_edge );

  return nb;
}


Collision_NS::Prim::Neighborhood Collision_NS::Edge::neighbourhood() const
{
  Neighborhood nb;

  nb.push_back( Edge( d_edge ) );
  
  nb.push_back( Face( d_edge ) );
  nb.push_back( Face( d_edge.sym() ) );

  QEdge_NS::Edge e = d_edge;

  while( ( e = e.lPrev() ) != d_edge )
  {
    nb.push_back( Edge( e ) );
    nb.push_back( Vert( e ) );
  }

  while( ( e = e.rPrev() ) != d_edge )
  {
    nb.push_back( Edge( e ) );
    nb.push_back( Vert( e.sym() ) );
  }

  return nb;
}


Collision_NS::Prim::Neighborhood Collision_NS::Face::neighbourhood() const
{
  Neighborhood nb;

  nb.push_back( Face( d_edge ) );

  QEdge_NS::Edge e = d_edge;
  do
  {
    nb.push_back( Edge( e ) );
    nb.push_back( Vert( e ) );
    e = e.lPrev();
  }
  while( e != d_edge );

  return nb;
}


Collision_NS::Vert::operator size_t() const
{
  return d_edge.o().id();
}


Collision_NS::Edge::operator size_t() const
{
  size_t n = d_edge.id();
  size_t s = d_edge.sym().id();
  return n < s ? n : s;
}


Collision_NS::Face::operator size_t() const
{
  return d_edge.l().id();
}


bool Collision_NS::operator == ( const Prim& a, const Prim& b )
{
  return a.operator size_t() == b.operator size_t();
}