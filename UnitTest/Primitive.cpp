#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Collision\Primitive.h"
#include <set>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( Neighborhood )
	{
    std::set<size_t> ids( const Collision_NS::Prim::Neighborhood& nb )
    {
      std::set<size_t> s;
      for( auto& p : nb ) s.insert( p );
      return s;
    }

	public:
		
    TEST_METHOD( Face )
		{
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();

      a.splice0( b.sym() );
      b.splice0( c.sym() );
      c.splice0( a.sym() );

      std::set<size_t> expected = 
      {
        //  face
        a.l().id(),
        //  edges
        a.id(),
        b.id(),
        c.id(),
        //  verts
        a.o().id(),
        b.o().id(),
        c.o().id()
      };

      Assert::AreEqual( 7u, expected.size() );

      Assert::IsTrue( expected == ids( Collision_NS::Face( a ).neighbourhood() ) );
		}


    TEST_METHOD( Edge )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();
      auto d = s.makeEdge();
      auto m = s.makeEdge();

      a.splice0( b.sym() );
      b.splice0( c.sym() );
      c.splice0( d.sym() );
      d.splice0( a.sym() );
      
      a.splice0( m );
      c.splice0( m.sym() );

      std::set<size_t> expected =
      {
        //  faces
        m.l().id(),
        m.r().id(),
        //  edges
        a.id(),
        b.id(),
        c.id(),
        d.id(),
        m.id(),
        //  verts
        a.o().id(),
        b.o().id(),
        c.o().id(),
        d.o().id(),
      };

      Assert::AreEqual( 11u, expected.size() );

      Assert::IsTrue( expected == ids( Collision_NS::Edge( m ).neighbourhood() ) );
    }


    TEST_METHOD( Vert )
    {
      QEdge_NS::Shape s;

      auto a = s.makeEdge();
      auto b = s.makeEdge();
      auto c = s.makeEdge();
      auto x = s.makeEdge();
      auto y = s.makeEdge();
      auto z = s.makeEdge();

      label( a, L"a" );
      label( b, L"b" );
      label( c, L"c" );
      label( x, L"x" );
      label( y, L"y" );
      label( z, L"z" );

      a.sym().splice0( b );
      b.sym().splice0( c );
      c.sym().splice0( a );

      Assert::AreEqual( b, a.lNext(), L"stage 1" );
      Assert::AreEqual( c, b.lNext(), L"stage 1" );
      Assert::AreEqual( a, c.lNext(), L"stage 1" );
      
      x.splice0( a );
      y.splice0( b );
      z.splice0( c );

      Assert::AreEqual( x, a.oNext(), L"stage 2" );
      Assert::AreEqual( y, b.oNext(), L"stage 2" );
      Assert::AreEqual( z, c.oNext(), L"stage 2" );

      Assert::AreEqual( c.sym(), x.oNext(), L"stage 2" );
      Assert::AreEqual( a.sym(), y.oNext(), L"stage 2" );
      Assert::AreEqual( b.sym(), z.oNext(), L"stage 2" );

      x.sym().splice0( y.sym() );
      y.sym().splice0( z.sym() );

      Assert::AreEqual( y, x.dNext(), L"stage 3" );
      Assert::AreEqual( z, y.dNext(), L"stage 3" );
      Assert::AreEqual( x, z.dNext(), L"stage 3" );

      std::set<size_t> expected =
      {
        //  faces
        x.l().id(),
        y.l().id(),
        z.l().id(),
        //  edges
        a.id(),
        b.id(),
        c.id(),
        x.id(),
        y.id(),
        z.id(),
        //  verts
        x.d().id(),
        a.o().id(),
        b.o().id(),
        c.o().id()
      };

      Assert::AreEqual( 13u, expected.size() );

      auto actual = Collision_NS::Vert( z.sym() ).neighbourhood();
      Assert::AreEqual( expected.size(), actual.size(), L"size" );

      auto actualID = ids( actual );
      Assert::AreEqual( expected.size(), actualID.size(), L"size ids" );

      Assert::IsTrue( expected == actualID );
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

      Assert::AreEqual<size_t>( a.l().id(), Collision_NS::Face( a ) );
      Assert::AreEqual<size_t>( b.l().id(), Collision_NS::Face( b ) );
      Assert::AreEqual<size_t>( c.l().id(), Collision_NS::Face( c ) );

      Assert::AreEqual<size_t>( a.r().id(), Collision_NS::Face( a.sym() ) );
      Assert::AreEqual<size_t>( b.r().id(), Collision_NS::Face( b.sym() ) );
      Assert::AreEqual<size_t>( c.r().id(), Collision_NS::Face( c.sym() ) );
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

      Assert::AreEqual<size_t>( a.id(), Collision_NS::Edge( a ) );
      Assert::AreEqual<size_t>( b.id(), Collision_NS::Edge( b ) );
      Assert::AreEqual<size_t>( c.id(), Collision_NS::Edge( c ) );

      Assert::AreEqual<size_t>( a.id(), Collision_NS::Edge( a.sym() ) );
      Assert::AreEqual<size_t>( b.id(), Collision_NS::Edge( b.sym() ) );
      Assert::AreEqual<size_t>( c.id(), Collision_NS::Edge( c.sym() ) );
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

      Assert::AreEqual<size_t>( a.o().id(), Collision_NS::Vert( a ) );
      Assert::AreEqual<size_t>( b.o().id(), Collision_NS::Vert( b ) );
      Assert::AreEqual<size_t>( c.o().id(), Collision_NS::Vert( c ) );

      Assert::AreEqual<size_t>( a.d().id(), Collision_NS::Vert( a.sym() ) );
      Assert::AreEqual<size_t>( b.d().id(), Collision_NS::Vert( b.sym() ) );
      Assert::AreEqual<size_t>( c.d().id(), Collision_NS::Vert( c.sym() ) );
    }
  };
}