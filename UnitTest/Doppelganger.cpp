#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Tailor/Doppelganger.h"
#include "Tetrahedron.h"
#include "Point3D.h"
#include "../QEdge/Utils.h"
#include "../Collision/AABBCollider.h"
#include "../Collision/PrimCollider.h"
#include "../Tailor/TopoGraph.h"
#include "../IO/Mesh.h"
#include <array>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Doppelganger )
  {
  public:

    TEST_METHOD( Twins )
    try
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

      doppel.shadow( graph );

      doppel.makeTwins( a, b );
      
      Assert::AreEqual( 3u, doppel.getDoppelgangerA().collection().size() );
      Assert::AreEqual( 3u, doppel.getDoppelgangerB().collection().size() );

      for( auto& i : doppel.getDoppelgangerA().collection() )
      {
        const Tailor_NS::TwinEdge& t = i.second.second;
        Assert::AreEqual( 1u, t.collection().size() );
      }

      for( auto& i : doppel.getDoppelgangerB().collection() )
      {
        const Tailor_NS::TwinEdge& t = i.second.second;
        Assert::AreEqual( 2u, t.collection().size() );
      }
    }
    catch( const std::exception& e )
    {
      Assert::IsTrue( false, ToString( e.what() ).c_str() );
    }
  };
}
