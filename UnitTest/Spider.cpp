#include "stdafx.h"
#include "CppUnitTest.h"
#include "Tetrahedron.h"
#include "Point3D.h"
#include "../QEdge/Utils.h"
#include "../Collision/AABBCollider.h"
#include "../Collision/PrimCollider.h"
#include "../Tailor/TopoGraph.h"
#include "../Tailor/Spider.h"
#include "../IO/Mesh.h"
#include "Intersection.h"
#include <set>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Spider )
  {
  public:

    TEST_METHOD( SpiderWeb )
    {
      Test_NS::Tetrahedron x, y;

      x.a.o().reset<Test_NS::Point3D>( 1, 0, 0 );
      x.b.o().reset<Test_NS::Point3D>( 0, 1, 0 );
      x.c.o().reset<Test_NS::Point3D>( 0, 0, 1 );
      x.A.o().reset<Test_NS::Point3D>( 0, 0, 0 );

      y.a.o().reset<Test_NS::Point3D>( 2, 0, 0 );
      y.b.o().reset<Test_NS::Point3D>( 0, 2, 0 );
      y.c.o().reset<Test_NS::Point3D>( 0, 0, 2 );
      y.A.o().reset<Test_NS::Point3D>( 0.2, 0.2, 0.2 );

      QEdge_NS::Shape& a = x.d_shape;
      QEdge_NS::Shape& b = y.d_shape;

      auto fa = QEdge_NS::allFaces( a );
      auto fb = QEdge_NS::allFaces( b );

      Math_NS::Grid grid{ box( a ) + box( b ) };

      Collision_NS::AABBTree ta( fa, grid );
      Collision_NS::AABBTree tb( fb, grid );

      Tailor_NS::TopoGraph graph;
      Test_NS::Intersection check;

      Assert::IsTrue( Collision_NS::AABBCollider{ Collision_NS::PrimCollider{ std::ref( graph ), grid } }.collide( ta, tb ) );
      Assert::IsTrue( Collision_NS::AABBCollider{ Collision_NS::PrimCollider{ std::ref( check ), grid } }.collide( ta, tb ) );

      Tailor_NS::Doppelganger doppel;
      Tailor_NS::Spider spider;

      doppel.shadow( graph );
      doppel.makeTwins();

      Tailor_NS::DeferSplice defer = spider.spin( graph, doppel );

      Assert::AreEqual( 3u, defer.collection().size() );
    }
  };
}
