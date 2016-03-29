#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Collision/PrimCollider.h"
#include "../QEdge/Utils.h"
#include "Intersection.h"
#include "Point3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  //  triangle ABC and edge UV
  struct TestIntersection
  {
    Math_NS::Grid               grid{ { { -16., -16., -16. }, { 16., 16., 16. } } };
    Test_NS::Intersection       graph;
    Collision_NS::PrimCollider  collider{ std::ref( graph ), grid };
    
    Math_NS::Vector3D           A;
    Math_NS::Vector3D           B;
    Math_NS::Vector3D           C;
    Math_NS::Vector3D           U;
    Math_NS::Vector3D           V;

    QEdge_NS::Shape             shape;

    QEdge_NS::Edge              a;
    QEdge_NS::Edge              b;
    QEdge_NS::Edge              c;
    QEdge_NS::Edge              e;


    TestIntersection()
    {
      a = shape.makeEdge();
      b = shape.makeEdge();
      c = shape.makeEdge();

      a.sym().splice0( b );
      b.sym().splice0( c );
      c.sym().splice0( a );

      e = shape.makeEdge();
    }


    bool collide()
    {
      a.o().reset<Test_NS::Point3D>( A );
      b.o().reset<Test_NS::Point3D>( B );
      c.o().reset<Test_NS::Point3D>( C );

      e.o().reset<Test_NS::Point3D>( U );
      e.d().reset<Test_NS::Point3D>( V );

      return collider( Collision_NS::Face( a ), Collision_NS::Edge( e ) );
    }


    //  check no intersections
    void test()
    {
      Assert::IsFalse( collide() );
    }


    //  check one intersection
    template <typename A, typename B>
    void test( A a, B b, const Math_NS::Vector3D& i )
    {
      Assert::IsTrue( collide() );

      Assert::AreEqual( 1u, graph.d_xpoints.size() );

      auto x = graph.d_xpoints.begin();

      Assert::AreEqual( i, x->second );

      Assert::AreEqual( id( a ), x->first.first, L"node.alpha" );
      Assert::AreEqual( id( b ), x->first.second, L"node.beta" );
    }


    //  check two intersections
    template <typename A1, typename B1, typename A2, typename B2>
    void test(
      A1 a1, B1 b1, const Math_NS::Vector3D& i1,
      A2 a2, B2 b2, const Math_NS::Vector3D& i2 )
    {
      Assert::IsTrue( collide() );

      Assert::AreEqual( 2u, graph.d_xpoints.size() );

      auto x1 = graph.d_xpoints.begin();
      auto x2 = x1;

      if( id( a1 ) == x1->first.first )
      {
        ++x2;
      }
      else
      {
        ++x1;
      }

      Assert::AreEqual( i1, x1->second );
      Assert::AreEqual( i2, x2->second );

      Assert::AreEqual( id( a1 ), x1->first.first, L"node1.alpha" );
      Assert::AreEqual( id( b1 ), x1->first.second, L"node1.beta" );

      Assert::AreEqual( id( a2 ), x2->first.first, L"node2.alpha" );
      Assert::AreEqual( id( b2 ), x2->first.second, L"node2.beta" );
    }
  };


  TEST_CLASS( Collider_FaceEdge_3D )
  {
    using F = Collision_NS::Face;
    using E = Collision_NS::Edge;
    using V = Collision_NS::Vert;

    //  Face + Edge @ 3D
    //  +FE+
    //  +FV+
    //  +EE+
    //  +EV+
    //  +VV+
  public:

    TEST_METHOD( FaceEdge_3D_FE )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 3, 0, 0 };
      t.C = { 0, 3, 0 };

      t.U = { 1, 1, -1 };
      t.V = { 1, 1, +1 };

      t.test( F( t.a ), E( t.e ), { 1, 1, 0 } );
    }

    TEST_METHOD( FaceEdge_3D_FV )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 3, 0, 0 };
      t.C = { 0, 3, 0 };

      t.U = { 1, 1, +0 };
      t.V = { 1, 1, +1 };

      t.test( F( t.a ), V( t.e ), { 1, 1, 0 } );
    }

    TEST_METHOD( FaceEdge_3D_EE )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 2, 0, 0 };
      t.C = { 0, 2, 0 };

      t.U = { 1, 1, -1 };
      t.V = { 1, 1, +1 };

      t.test( E( t.b ), E( t.e ), { 1, 1, 0 } );
    }

    TEST_METHOD( FaceEdge_3D_EV )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 2, 0, 0 };
      t.C = { 0, 2, 0 };

      t.U = { 1, 1, +0 };
      t.V = { 1, 1, +1 };

      t.test( E( t.b ), V( t.e ), { 1, 1, 0 } );
    }

    TEST_METHOD( FaceEdge_3D_VV )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 3, 0, 0 };
      t.C = { 0, 3, 0 };

      t.U = { 0, 0, 0 };
      t.V = { 1, 1, 1 };

      t.test( V( t.a ), V( t.e ), { 0, 0, 0 } );
    }
  };


  TEST_CLASS( Collider_FaceEdge_2D )
  {
    using F = Collision_NS::Face;
    using E = Collision_NS::Edge;
    using V = Collision_NS::Vert;

    //  Face + Edge @ 2D
    //  +FE+
    //  +FV+
    //  +EE+
    //  +EV+
    //  +VV+
  public:

    TEST_METHOD( FaceEdge_2D_FE )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 3, 0, 0 };
      t.C = { 0, 3, 0 };

      t.U = { 3, 3, 0 };
      t.V = { 5, 5, 0 };

      t.test();
    }

    TEST_METHOD( FaceEdge_2D_FV )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 6, 0, 0 };
      t.C = { 0, 6, 0 };

      t.U = { 1, 1, 0 };
      t.V = { 2, 2, 0 };

      t.test( F( t.a ), V( t.e ), { 1, 1, 0 }, F( t.a ), V( t.e.sym() ), { 2, 2, 0 } );
    }

    TEST_METHOD( FaceEdge_2D_EE )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 2, 0, 0 };
      t.C = { 0, 2, 0 };

      t.U = { -1, 1, 0 };
      t.V = { 2, 1, 0 };

      t.test( E( t.b ), E( t.e ), { 1, 1, 0 }, E( t.c ), E( t.e ), { 0, 1, 0 } );
    }

    TEST_METHOD( FaceEdge_2D_EV )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 2, 0, 0 };
      t.C = { 0, 2, 0 };

      t.U = { 1, 1, 0 };
      t.V = { 2, 2, 0 };

      t.test( E( t.b ), V( t.e ), { 1, 1, 0 } );
    }

    TEST_METHOD( FaceEdge_2D_VV )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 2, 0, 0 };
      t.C = { 0, 2, 0 };

      t.U = { 0, 0, 0 };
      t.V = { -1, -1, 0 };

      t.test( V( t.a ), V( t.e ), { 0, 0, 0 } );
    }
  };


  TEST_CLASS( Collider_FaceEdge_1D )
  {
    using F = Collision_NS::Face;
    using E = Collision_NS::Edge;
    using V = Collision_NS::Vert;

    //  Face + Edge @ 1D
    //  -FE-
    //  -FV-
    //  -EE-
    //  +EV+
    //  +VV+
  public:

    TEST_METHOD( FaceEdge_1D_EV )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 2, 0, 0 };
      t.C = { 0, 2, 0 };

      t.U = { 1, 0, 0 };
      t.V = { 3, 0, 0 };

      t.test( E( t.a ), V( t.e ), { 1, 0, 0 }, V( t.b ), E( t.e ), { 2, 0, 0 } );
    }

    TEST_METHOD( FaceEdge_1D_VV )
    {
      TestIntersection t;

      t.A = { 0, 0, 0 };
      t.B = { 1, 0, 0 };
      t.C = { 0, 1, 0 };

      t.U = { 1, 0, 0 };
      t.V = { 2, 0, 0 };

      t.test( V( t.b ), V( t.e ), { 1, 0, 0 } );
    }
  };
}