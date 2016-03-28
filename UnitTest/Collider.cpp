#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Collision\Graph.h"
#include "..\Collision\PrimCollider.h"
#include "../QEdge/Utils.h"
#include "Point3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  struct TestIntersection
  {
    Math_NS::Grid               grid{ { { -16., -16., -16. }, { 16., 16., 16. } } };
    Collision_NS::Graph         graph;
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


    void test()
    {
      Assert::IsFalse( collide() );
    }


    template <typename A, typename B>
    void test( A a, B b, const Math_NS::Vector3D& i )
    {
      Assert::IsTrue( collide() );

      auto all = allVerts( graph.graph() );

      Assert::AreEqual( 1u, all.size() );

      QEdge_NS::Edge n = all.front();

      Assert::AreEqual( i, n.o()->point() );

      auto xid = dynamic_cast<Collision_NS::XPointID*>( &*n.o() );

      Assert::IsNotNull( xid );
      Assert::AreEqual( id( a ), xid->alphaId(), L"node.alpha" );
      Assert::AreEqual( id( b ), xid->betaId(), L"node.beta" );
    }


    template <typename A1, typename B1, typename A2, typename B2>
    void test(
      A1 a1, B1 b1, const Math_NS::Vector3D& i1,
      A2 a2, B2 b2, const Math_NS::Vector3D& i2 )
    {
      Assert::IsTrue( collide() );

      auto all = allVerts( graph.graph() );

      Assert::AreEqual( 2u, all.size() );

      QEdge_NS::Edge* n1 = &all.front();
      QEdge_NS::Edge* n2 = &all.back();

      auto xid1 = dynamic_cast<Collision_NS::XPointID*>( &*n1->o() );
      auto xid2 = dynamic_cast<Collision_NS::XPointID*>( &*n2->o() );

      Assert::IsNotNull( xid1 );
      Assert::IsNotNull( xid2 );

      if( id( a1 ) != xid1->alphaId() || id( b1 ) != xid1->betaId() )
      {
        std::swap( n1, n2 );
        std::swap( xid1, xid2 );
      }

      Assert::AreEqual( i1, n1->o()->point() );
      Assert::AreEqual( i2, n2->o()->point() );

      Assert::AreEqual<size_t>( id( a1 ), xid1->alphaId(), L"node1.alpha" );
      Assert::AreEqual<size_t>( id( b1 ), xid1->betaId(), L"node1.beta" );

      Assert::AreEqual<size_t>( id( a2 ), xid2->alphaId(), L"node2.alpha" );
      Assert::AreEqual<size_t>( id( b2 ), xid2->betaId(), L"node2.beta" );
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