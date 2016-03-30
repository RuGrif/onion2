#include "stdafx.h"
#include "CppUnitTest.h"
#include "Tetrahedron.h"
#include "Point3D.h"
#include "../QEdge/Utils.h"
#include "../Collision/AABBCollider.h"
#include "../Collision/PrimCollider.h"
#include "../Tailor/Graph.h"
#include "../IO/Mesh.h"
#include <set>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Graph )
  {
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

      Tailor_NS::Graph inter;

      Collision_NS::AABBTree ta( fa, grid );
      Collision_NS::AABBTree tb( fb, grid );

      Collision_NS::PrimCollider pc{ std::ref( inter ), grid };
      Collision_NS::AABBCollider c{ pc };

      Assert::IsTrue( c.collide( ta, tb ) );

      Assert::AreEqual( inter.d_alpha.d_edges.size(), inter.d_beta.d_edges.size() );

      auto va = allVerts( inter.d_alpha.d_cut );
      auto vb = allVerts( inter.d_alpha.d_cut );

      Assert::AreEqual( va.size(), vb.size() );

      std::multiset<std::tuple<double, double, double>> vac, vbc;

      for( auto e : va )
      {
        Assert::IsTrue( e.o() );
        auto p = e.o()->point();
        vac.emplace( p.x, p.y, p.z );
      }

      for( auto e : vb )
      {
        Assert::IsTrue( e.o() );
        auto p = e.o()->point();
        vbc.emplace( p.x, p.y, p.z );
      }

      Assert::IsTrue( vac == vbc, L"intersection coordinates" );

      IO_NS::writeMesh( inter.d_alpha.d_cut, L"Graph.alpha.mesh" );
      IO_NS::writeMesh( inter.d_beta.d_cut, L"Graph.beta.mesh" );
    }
  };
}
