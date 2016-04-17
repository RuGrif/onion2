#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Tailor/Doppelganger.h"
#include "Tetrahedron.h"
#include "Point3D.h"
#include "../QEdge/Utils.h"
#include "../Collision/AABBCollider.h"
#include "../Collision/PrimCollider.h"
#include "../Tailor/Graph.h"
#include "../IO/Mesh.h"
#include <array>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Doppelganger )
  {
  public:

    TEST_METHOD( Forgery )
    {
      Test_NS::Tetrahedron x, y;

      x.a.o().reset<Test_NS::Point3D>( 1, 0, 0 );
      x.b.o().reset<Test_NS::Point3D>( 0, 1, 0 );
      x.c.o().reset<Test_NS::Point3D>( 0, 0, 1 );
      x.A.o().reset<Test_NS::Point3D>( 0, 0, 0 );

      y.a.o().reset<Test_NS::Point3D>( 4, 3, 3 );
      y.b.o().reset<Test_NS::Point3D>( 3, 4, 3 );
      y.c.o().reset<Test_NS::Point3D>( 3, 3, 4 );
      y.A.o().reset<Test_NS::Point3D>( -1, -1, -1 );

      QEdge_NS::Shape& a = x.d_shape;
      QEdge_NS::Shape& b = y.d_shape;

      IO_NS::writeMesh( a, L"Forgery.A.in.mesh" );
      IO_NS::writeMesh( b, L"Forgery.B.in.mesh" );

      auto fa = QEdge_NS::allFaces( a );
      auto fb = QEdge_NS::allFaces( b );

      Math_NS::Grid grid{ box( a ) + box( b ) };

      Collision_NS::AABBTree ta( fa, grid );
      Collision_NS::AABBTree tb( fb, grid );

      Tailor_NS::TopoGraph graph;

      Assert::IsTrue( Collision_NS::AABBCollider{ Collision_NS::PrimCollider{ std::ref( graph ), grid } }.collide( ta, tb ) );

      Tailor_NS::Doppelganger doppel;

      graph.forEachXPoint( std::ref( doppel ) );

      doppel.forgery( a, b );

      IO_NS::writeMesh( a, L"Forgery.A.out.mesh" );
      IO_NS::writeMesh( b, L"Forgery.B.out.mesh" );

      Assert::AreEqual<size_t>( 4 + 3, QEdge_NS::allVerts( a ).size() );
      Assert::AreEqual<size_t>( 4 + 2 * 3, QEdge_NS::allVerts( b ).size() );

      for( QEdge_NS::Edge e : { y.a.oPrev(), y.b.oPrev(), y.c.oPrev() } )
      {
        std::array<Math_NS::Vector3D, 4> p;

        for( size_t i = 0; i < p.size(); ++i )
        {
          p[ i ] = e.o()->point();
          e = e.lNext();
        }

        //  sorting check
        std::array<double, 4> d;

        for( size_t i = 0; i < d.size(); ++i )
        {
          Math_NS::Vector3D v = p[ i ] - p[ 0 ];
          d[ i ] = v * v;
        }

        for( size_t i = 0; i + 1 < d.size(); ++i )
        {
          Assert::IsTrue( d[ i ] < d[ i + 1 ] );
        }
      }
    }
  };
}