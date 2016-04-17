#include "GeoLocation.h"


Collision_NS::Face Tailor_NS::getFace( Collision_NS::Vert v )
{
  auto eid = []( QEdge_NS::Edge x ) { return id( Collision_NS::Edge{ x } ); };
  
  QEdge_NS::Edge o = v.e();
  size_t min = eid( o );
  
  for( QEdge_NS::Edge i = v.e(); ( i = i.oNext() ) != v.e(); )
  {
    size_t cur = eid( i );
    if( cur < min )
    {
      o = i;
      min = cur;
    }
  }

  return{ o };
}