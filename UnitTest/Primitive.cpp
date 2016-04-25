#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Collision/Primitive.h"
#include "Tetrahedron.h"
#include <set>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( Neighborhood )
  {
    template <typename A, typename B>
    void check( A a, B b )
    {
      std::set<std::pair<size_t, size_t>> ids;

      a.forEachNb( [&ids, b]( auto, auto pa )
      {
        b.forEachNb( [&ids, pa]( auto, auto pb )
        {
          Assert::IsTrue( ids.insert( { id( pa ), id( pb ) } ).second );
        } );
      } );
    }

  public:
    
    TEST_METHOD( UniqueNbId )
    {
      Test_NS::Tetrahedron x, y;

      using V = Collision_NS::Vert;
      using E = Collision_NS::Edge;
      using F = Collision_NS::Face;

      check<V, V>( x.a, y.a );
      check<V, E>( x.a, y.a );
      check<V, F>( x.a, y.a );
      check<E, V>( x.a, y.a );
      check<E, E>( x.a, y.a );
      check<E, F>( x.a, y.a );
      check<F, V>( x.a, y.a );
      check<F, E>( x.a, y.a );
    }
  };


  TEST_CLASS( PrimitiveId )
  {
  public:
    
    TEST_METHOD( FaceId )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();

      a.splice0( b.sym() );
      b.splice0( c.sym() );
      c.splice0( a.sym() );

      Assert::AreEqual( a.l().id(), b.l().id() );
      Assert::AreEqual( c.l().id(), c.l().id() );

      Assert::AreEqual<size_t>( a.l().id(), id( Collision_NS::Face( a ) ) );
      Assert::AreEqual<size_t>( b.l().id(), id( Collision_NS::Face( b ) ) );
      Assert::AreEqual<size_t>( c.l().id(), id( Collision_NS::Face( c ) ) );

      Assert::AreEqual<size_t>( a.r().id(), id( Collision_NS::Face( a.sym() ) ) );
      Assert::AreEqual<size_t>( b.r().id(), id( Collision_NS::Face( b.sym() ) ) );
      Assert::AreEqual<size_t>( c.r().id(), id( Collision_NS::Face( c.sym() ) ) );
    }


    TEST_METHOD( EdgeId )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();

      a.splice0( b.sym() );
      b.splice0( c.sym() );
      c.splice0( a.sym() );

      Assert::AreEqual<size_t>( a.id(), id( Collision_NS::Edge( a ) ) );
      Assert::AreEqual<size_t>( b.id(), id( Collision_NS::Edge( b ) ) );
      Assert::AreEqual<size_t>( c.id(), id( Collision_NS::Edge( c ) ) );

      Assert::AreEqual<size_t>( a.id(), id( Collision_NS::Edge( a.sym() ) ) );
      Assert::AreEqual<size_t>( b.id(), id( Collision_NS::Edge( b.sym() ) ) );
      Assert::AreEqual<size_t>( c.id(), id( Collision_NS::Edge( c.sym() ) ) );
    }


    TEST_METHOD( VertId )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();

      a.splice0( b.sym() );
      b.splice0( c.sym() );
      c.splice0( a.sym() );

      Assert::AreEqual<size_t>( a.o().id(), id( Collision_NS::Vert( a ) ) );
      Assert::AreEqual<size_t>( b.o().id(), id( Collision_NS::Vert( b ) ) );
      Assert::AreEqual<size_t>( c.o().id(), id( Collision_NS::Vert( c ) ) );

      Assert::AreEqual<size_t>( a.d().id(), id( Collision_NS::Vert( a.sym() ) ) );
      Assert::AreEqual<size_t>( b.d().id(), id( Collision_NS::Vert( b.sym() ) ) );
      Assert::AreEqual<size_t>( c.d().id(), id( Collision_NS::Vert( c.sym() ) ) );
    }
  };

  TEST_CLASS( Major )
  {
  public:
    
    TEST_METHOD( Vert )
    {
      Test_NS::Tetrahedron t;

      Assert::AreEqual( id( major( Collision_NS::Vert( t.A ) ) ), id( major( Collision_NS::Vert( t.B ) ) ) );
      Assert::AreEqual( id( major( Collision_NS::Vert( t.B ) ) ), id( major( Collision_NS::Vert( t.C ) ) ) );

      Assert::AreNotEqual( id( major( Collision_NS::Vert( t.a ) ) ), id( major( Collision_NS::Vert( t.A ) ) ) );
    }

    TEST_METHOD( Edge )
    {
      Test_NS::Tetrahedron t;

      Assert::AreEqual( id( major( Collision_NS::Edge( t.a ) ) ), id( major( Collision_NS::Edge( t.a.sym() ) ) ) );

      Assert::AreNotEqual( id( major( Collision_NS::Edge( t.a ) ) ), id( major( Collision_NS::Edge( t.b ) ) ) );
    }

    TEST_METHOD( Face )
    {
      Test_NS::Tetrahedron t;

      Assert::AreEqual( id( major( Collision_NS::Face( t.a ) ) ), id( major( Collision_NS::Face( t.b ) ) ) );
      Assert::AreEqual( id( major( Collision_NS::Face( t.a ) ) ), id( major( Collision_NS::Face( t.c ) ) ) );

      Assert::AreNotEqual( id( major( Collision_NS::Face( t.a ) ) ), id( major( Collision_NS::Face( t.A ) ) ) );
    }
  };
}