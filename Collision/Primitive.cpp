#include "Primitive.h"


Collision_NS::Prim::Neighborhood Collision_NS::Vert::neighbourhood() const
{
  Neighborhood nb;

  nb.push_back( std::make_unique<Vert>( d_edge ) );

  QEdge_NS::Edge e = d_edge;
  do
  {
    nb.push_back( std::make_unique<Edge>( e ) );
    nb.push_back( std::make_unique<Vert>( e.sym() ) );
    nb.push_back( std::make_unique<Face>( e ) );
    nb.push_back( std::make_unique<Edge>( e.lNext() ) );
    e = e.oNext();
  }
  while( e != d_edge );

  return nb;
}


Collision_NS::Prim::Neighborhood Collision_NS::Edge::neighbourhood() const
{
  Neighborhood nb;

  nb.push_back( std::make_unique<Edge>( d_edge ) );
  
  nb.push_back( std::make_unique<Face>( d_edge ) );
  nb.push_back( std::make_unique<Face>( d_edge.sym() ) );

  QEdge_NS::Edge e = d_edge;

  while( ( e = e.lPrev() ) != d_edge )
  {
    nb.push_back( std::make_unique<Edge>( e ) );
    nb.push_back( std::make_unique<Vert>( e ) );
  }

  while( ( e = e.rPrev() ) != d_edge )
  {
    nb.push_back( std::make_unique<Edge>( e ) );
    nb.push_back( std::make_unique<Vert>( e.sym() ) );
  }

  return nb;
}


Collision_NS::Prim::Neighborhood Collision_NS::Face::neighbourhood() const
{
  Neighborhood nb;

  nb.push_back( std::make_unique<Face>( d_edge ) );

  QEdge_NS::Edge e = d_edge;
  do
  {
    nb.push_back( std::make_unique<Edge>( e ) );
    nb.push_back( std::make_unique<Vert>( e ) );
    e = e.lPrev();
  }
  while( e != d_edge );

  return nb;
}


std::unique_ptr<Collision_NS::Prim> Collision_NS::Vert::copy() const
{
  return std::make_unique<Vert>( d_edge );
}


size_t Collision_NS::Vert::id() const
{
  return reinterpret_cast<size_t>( &d_edge.o() );
}


std::unique_ptr<Collision_NS::Prim> Collision_NS::Edge::copy() const
{
  return std::make_unique<Edge>( d_edge );
}


size_t Collision_NS::Edge::id() const
{
  size_t n = reinterpret_cast<size_t>( &d_edge.n() );
  size_t s = reinterpret_cast<size_t>( &d_edge.s() );
  return n < s ? n : s;
}


std::unique_ptr<Collision_NS::Prim> Collision_NS::Face::copy() const
{
  return std::make_unique<Face>( d_edge );
}


size_t Collision_NS::Face::id() const
{
  return reinterpret_cast<size_t>( &d_edge.l() );
}


bool Collision_NS::operator == ( const Prim& a, const Prim& b )
{
  return a.id() == b.id();
}