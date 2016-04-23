#include "Cut.h"
#include "Spider.h"
#include "Doppelganger.h"
#include "DeferSplice.h"
#include "../QEdge/Utils.h"
#include "../Math/Grid.h"
#include "../Collision/AABB.h"
#include "../Collision/AABBCollider.h"
#include "../Collision/PrimCollider.h"


Tailor_NS::TopoGraph Tailor_NS::intersect( QEdge_NS::Shape& a, QEdge_NS::Shape& b )
{
  Math_NS::Grid grid{ box( a ) + box( b ) };

  auto fa = QEdge_NS::allFaces( a );
  auto fb = QEdge_NS::allFaces( b );

  Collision_NS::AABBTree ta{ fa, grid };
  Collision_NS::AABBTree tb{ fb, grid };

  Tailor_NS::TopoGraph graph;

  Collision_NS::PrimCollider primCollider{ std::ref( graph ), grid };
  Collision_NS::AABBCollider aabbCollider{ std::ref( primCollider ) };
  
  aabbCollider.collide( ta, tb );

  return graph;
}


void Tailor_NS::cut( QEdge_NS::Shape& a, QEdge_NS::Shape& b, const TopoGraph& g )
{
  //
  //  create twins for interseected edges
  //
  Doppelganger doppelganger;
  doppelganger.shadow( g );
  doppelganger.makeTwins( a, b );

  //
  //  build new edges for intersection graph
  //
  Spider spider;
  DeferSplice defer = spider.spin( g, doppelganger );
  
  defer.splice();

  //
  //  merge intersection edges into shape
  //
  a.merge( std::move( spider.webA() ) );
  b.merge( std::move( spider.webB() ) );
  
  doppelganger.substitute();

  a.cleanup();
  b.cleanup();
}
