#include "Primitive.h"


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