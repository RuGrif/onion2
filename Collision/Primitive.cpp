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


namespace
{
  QEdge_NS::Edge major( QEdge_NS::Edge e, QEdge_NS::Edge( QEdge_NS::Edge::* next )( void ) const )
  {
    QEdge_NS::Edge m = e;

    for( QEdge_NS::Edge i = e; ( i = ( i.*next )() ) != e; )
    {
      if( i.id() < m.id() ) m = i;
    }
    
    return m;
  }
}


Collision_NS::Vert Collision_NS::major( Vert v )
{
  return ::major( v.e(), &QEdge_NS::Edge::oNext );
}


Collision_NS::Edge Collision_NS::major( Edge e )
{
  return e.isMajor() ? e.e() : e.e().sym();
}


Collision_NS::Face Collision_NS::major( Face f )
{
  return ::major( f.e(), &QEdge_NS::Edge::lNext );
}