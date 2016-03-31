#include "stdafx.h"
#include "CppUnitTest.h"
#include "Tetrahedron.h"
#include "Point3D.h"
#include "../QEdge/Utils.h"
#include "../Collision/AABBCollider.h"
#include "../Collision/PrimCollider.h"
#include "../Tailor/Graph.h"
#include "../IO/Mesh.h"
#include "Intersection.h"
#include <set>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Graph )
  {
    struct XEdgesCallback
    {
      using Map = std::map<Collision_NS::XPointID, Math_NS::Vector3D>;
      
      Map d_points0;
      Map d_points1;

      template <typename A0, typename B0, typename A1, typename B1>
      void operator() ( const Collision_NS::XPoint<A0, B0>& p0, const Collision_NS::XPoint<A1, B1>& p1 )
      {
        d_points0[ makeXPointID( p0.first, p0.second ) ] = point( p0 );
        d_points1[ makeXPointID( p1.first, p1.second ) ] = point( p1 );
      }
    };

  public:

    TEST_METHOD( Tetrahedron )
    {
      Test_NS::Tetrahedron x, y;

      x.a.o().reset<Test_NS::Point3D>( 1, 0, 0 );
      x.b.o().reset<Test_NS::Point3D>( 0, 1, 0 );
      x.c.o().reset<Test_NS::Point3D>( 0, 0, 1 );
      x.A.o().reset<Test_NS::Point3D>( 0, 0, 0 );

      y.a.o().reset<Test_NS::Point3D>( 8, 9, 11 );
      y.b.o().reset<Test_NS::Point3D>( 12, 13, 14 );
      y.c.o().reset<Test_NS::Point3D>( -15, -16, -17 );
      y.A.o().reset<Test_NS::Point3D>( -10, -10, -10 );

      QEdge_NS::Shape& a = x.d_shape;
      QEdge_NS::Shape& b = y.d_shape;

      auto fa = QEdge_NS::allFaces( a );
      auto fb = QEdge_NS::allFaces( b );

      Math_NS::Grid grid{ box( a ) + box( b ) };

      Collision_NS::AABBTree ta( fa, grid );
      Collision_NS::AABBTree tb( fb, grid );

      Tailor_NS::Graph graph;
      Test_NS::Intersection check;

      Assert::IsTrue( Collision_NS::AABBCollider{ Collision_NS::PrimCollider{ std::ref( graph ), grid } }.collide( ta, tb ) );
      Assert::IsTrue( Collision_NS::AABBCollider{ Collision_NS::PrimCollider{ std::ref( check ), grid } }.collide( ta, tb ) );

      XEdgesCallback cb;

      graph.forEachXEdge( std::ref( cb ) );

      Assert::IsTrue( cb.d_points0 == check.d_xpoints, L"points0" );
      Assert::IsTrue( cb.d_points1 == check.d_xpoints, L"points1" );
    }
  };
}
