#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Collision\Collider.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  namespace
  {
    struct Point : public QEdge_NS::VertData
    {
      Point() = default;
      Point( const Math_NS::Vector3D& i_point ) : d_point( i_point ) {}
      Point( double x, double y, double z ) : d_point( x, y, z ) {}

      virtual Math_NS::Vector3D point() const { return d_point; }
      virtual void point( const Math_NS::Vector3D& i_point ) { d_point = i_point; }

    private:

      Math_NS::Vector3D d_point;
    };
  }


  TEST_CLASS( Collider_EdgeFace_3D )
  {
  public:

    TEST_METHOD( EdgeFace )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();

      a.sym().splice0( b );
      b.sym().splice0( c );
      c.sym().splice0( a );

      a.o().reset<Point>( 0, 0, 0 );
      b.o().reset<Point>( 3, 0, 0 );
      c.o().reset<Point>( 0, 3, 0 );

      auto e = s.makeEdge();

      e.o().reset<Point>( 1, 1, -1 );
      e.d().reset<Point>( 1, 1, +1 );

      Collision_NS::Collider collider;

      bool r = collider( Collision_NS::Face( a ), Collision_NS::Edge( e ) );

      Assert::IsTrue( r );

      auto all = collider.graph().all();

      Assert::AreEqual( 1u, all.size() );

      const Collision_NS::Node& n = all.front();

      Assert::AreEqual( Math_NS::Vector3D( 1, 1, 0 ), n.intersection() );

      Assert::AreEqual<size_t>( Collision_NS::Face( a ), n.alpha() );
      Assert::AreEqual<size_t>( Collision_NS::Edge( e ), n.beta() );
    }


    TEST_METHOD( VertFace )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();

      a.sym().splice0( b );
      b.sym().splice0( c );
      c.sym().splice0( a );

      a.o().reset<Point>( 0, 0, 0 );
      b.o().reset<Point>( 3, 0, 0 );
      c.o().reset<Point>( 0, 3, 0 );

      auto e = s.makeEdge();

      e.o().reset<Point>( 1, 1, 0 );
      e.d().reset<Point>( 1, 1, +1 );

      Collision_NS::Collider collider;

      bool r = collider( Collision_NS::Face( a ), Collision_NS::Edge( e ) );

      Assert::IsTrue( r );

      auto all = collider.graph().all();

      Assert::AreEqual( 1u, all.size() );

      const Collision_NS::Node& n = all.front();

      Assert::AreEqual( Math_NS::Vector3D( 1, 1, 0 ), n.intersection() );

      Assert::AreEqual<size_t>( Collision_NS::Face( a ), n.alpha() );
      Assert::AreEqual<size_t>( Collision_NS::Vert( e ), n.beta() );
    }

    TEST_METHOD( EdgeEdge )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();

      a.sym().splice0( b );
      b.sym().splice0( c );
      c.sym().splice0( a );

      a.o().reset<Point>( 0, 0, 0 );
      b.o().reset<Point>( 2, 0, 0 );
      c.o().reset<Point>( 0, 2, 0 );

      auto e = s.makeEdge();

      e.o().reset<Point>( 1, 1, -1 );
      e.d().reset<Point>( 1, 1, +1 );

      Collision_NS::Collider collider;

      bool r = collider( Collision_NS::Face( a ), Collision_NS::Edge( e ) );

      Assert::IsTrue( r );

      auto all = collider.graph().all();

      Assert::AreEqual( 1u, all.size() );

      const Collision_NS::Node& n = all.front();

      Assert::AreEqual( Math_NS::Vector3D( 1, 1, 0 ), n.intersection() );

      Assert::AreEqual<size_t>( Collision_NS::Edge( b ), n.alpha() );
      Assert::AreEqual<size_t>( Collision_NS::Edge( e ), n.beta() );
    }


    TEST_METHOD( VertEdge )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();

      a.sym().splice0( b );
      b.sym().splice0( c );
      c.sym().splice0( a );

      a.o().reset<Point>( 0, 0, 0 );
      b.o().reset<Point>( 2, 0, 0 );
      c.o().reset<Point>( 0, 2, 0 );

      auto e = s.makeEdge();

      e.o().reset<Point>( 1, 1, 0 );
      e.d().reset<Point>( 1, 1, +1 );

      Collision_NS::Collider collider;

      bool r = collider( Collision_NS::Face( a ), Collision_NS::Edge( e ) );

      Assert::IsTrue( r );

      auto all = collider.graph().all();

      Assert::AreEqual( 1u, all.size() );

      const Collision_NS::Node& n = all.front();

      Assert::AreEqual( Math_NS::Vector3D( 1, 1, 0 ), n.intersection() );

      Assert::AreEqual<size_t>( Collision_NS::Edge( b ), n.alpha() );
      Assert::AreEqual<size_t>( Collision_NS::Vert( e ), n.beta() );
    }


    TEST_METHOD( VertVert )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();

      a.sym().splice0( b );
      b.sym().splice0( c );
      c.sym().splice0( a );

      a.o().reset<Point>( 0, 0, 0 );
      b.o().reset<Point>( 1, 0, 0 );
      c.o().reset<Point>( 0, 1, 0 );

      auto e = s.makeEdge();

      e.o().reset<Point>( 1, 0, 0 );
      e.d().reset<Point>( 1, 1, 1 );

      Collision_NS::Collider collider;

      bool r = collider( Collision_NS::Face( a ), Collision_NS::Edge( e ) );

      Assert::IsTrue( r );

      auto all = collider.graph().all();

      Assert::AreEqual( 1u, all.size() );

      const Collision_NS::Node& n = all.front();

      Assert::AreEqual( Math_NS::Vector3D( 1, 0, 0 ), n.intersection() );

      Assert::AreEqual<size_t>( Collision_NS::Vert( b ), n.alpha() );
      Assert::AreEqual<size_t>( Collision_NS::Vert( e ), n.beta() );
    }
  };
}