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
    struct XVertCB
    {
      using Map = std::map<Collision_NS::XPointID, Math_NS::Vector3D>;
      
      Map d_points;

      template <typename P>
      void operator() ( const P& p )
      {
        d_points[ makeXPointID( p ) ] = point( p );
      }
    };

    struct XEdgeCB
    {
      using EID = std::pair<Collision_NS::XPointID, Collision_NS::XPointID>;

      XVertCB d_alpha;
      XVertCB d_beta;
            
      std::map<EID, size_t> d_posEdges;
      std::map<EID, size_t> d_negEdges;

      template <typename A0, typename B0, typename A1, typename B1>
      void operator() ( const Collision_NS::XPoint<A0, B0>& p0, const Collision_NS::XPoint<A1, B1>& p1 )
      {
        d_alpha( p0 );
        d_beta( p1 );

        ++d_posEdges[ { makeXPointID( p0 ), makeXPointID( p1 ) } ];
        ++d_negEdges[ { makeXPointID( p1 ), makeXPointID( p0 ) } ];
      }
    };

  public:

    TEST_METHOD( XEdgesCallback )
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

      Tailor_NS::Graph graph;
      Test_NS::Intersection check;

      Assert::IsTrue( Collision_NS::AABBCollider{ Collision_NS::PrimCollider{ std::ref( graph ), grid } }.collide( ta, tb ) );
      Assert::IsTrue( Collision_NS::AABBCollider{ Collision_NS::PrimCollider{ std::ref( check ), grid } }.collide( ta, tb ) );

      XEdgeCB cb;

      graph.forEachXEdge( std::ref( cb ) );

      Assert::IsTrue( cb.d_alpha.d_points == check.d_xpoints, L"points0" );
      Assert::IsTrue( cb.d_beta.d_points == check.d_xpoints, L"points1" );

      Assert::IsTrue( cb.d_posEdges == cb.d_negEdges, L"N pos = N neg" );

      for( const auto& e : cb.d_posEdges )
      {
        Assert::AreEqual( 1u, e.second, L"num of edge cb calls" );
      }

      Assert::AreEqual( 3u, cb.d_posEdges.size() );

      XVertCB v0;

      graph.forEachXPoint( std::ref( v0 ) );

      Assert::IsTrue( v0.d_points == check.d_xpoints, L"points" );
    }
  };
}
