#include "Primitive.h"


std::vector<size_t> Collision_NS::nb( Vert x )
{
  std::vector<size_t> n;

  n.push_back( id( x ) );

  QEdge_NS::Edge e = x.e();
  do
  {
    n.push_back( id( Edge( e ) ) );
    n.push_back( id( Vert( e.sym() ) ) );
    n.push_back( id( Face( e ) ) );
    n.push_back( id( Edge( e.lNext() ) ) );
    e = e.oNext();
  }
  while( e != x.e() );

  return n;
}


std::vector<size_t> Collision_NS::nb( Edge x )
{
  std::vector<size_t> n;

  n.push_back( id( x ) );
  
  n.push_back( id( Face( x.e() ) ) );
  n.push_back( id( Face( x.e().sym() ) ) );

  QEdge_NS::Edge e = x.e();

  while( ( e = e.lPrev() ) != x.e() )
  {
    n.push_back( id( Edge( e ) ) );
    n.push_back( id( Vert( e ) ) );
  }

  while( ( e = e.rPrev() ) != x.e() )
  {
    n.push_back( id( Edge( e ) ) );
    n.push_back( id( Vert( e.sym() ) ) );
  }

  return n;
}


std::vector<size_t> Collision_NS::nb( Face x )
{
  std::vector<size_t> n;

  n.push_back( id( x ) );

  QEdge_NS::Edge e = x.e();
  do
  {
    n.push_back( id( Edge( e ) ) );
    n.push_back( id( Vert( e ) ) );
    e = e.lPrev();
  }
  while( e != x.e() );

  return n;
}
