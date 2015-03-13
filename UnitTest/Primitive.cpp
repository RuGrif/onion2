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
      for( auto& p : nb ) s.insert( p->id() );
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
        reinterpret_cast<size_t>( &a.l() ),
        //  edges
        reinterpret_cast<size_t>( &a.n() ),
        reinterpret_cast<size_t>( &b.n() ),
        reinterpret_cast<size_t>( &c.n() ),
        //  verts
        reinterpret_cast<size_t>( &a.o() ),
        reinterpret_cast<size_t>( &b.o() ),
        reinterpret_cast<size_t>( &c.o() ),
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
        reinterpret_cast<size_t>( &m.l() ),
        reinterpret_cast<size_t>( &m.r() ),
        //  edges
        reinterpret_cast<size_t>( &a.n() ),
        reinterpret_cast<size_t>( &b.n() ),
        reinterpret_cast<size_t>( &c.n() ),
        reinterpret_cast<size_t>( &d.n() ),
        reinterpret_cast<size_t>( &m.n() ),
        //  verts
        reinterpret_cast<size_t>( &a.o() ),
        reinterpret_cast<size_t>( &b.o() ),
        reinterpret_cast<size_t>( &c.o() ),
        reinterpret_cast<size_t>( &d.o() ),
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
        reinterpret_cast<size_t>( &x.l() ),
        reinterpret_cast<size_t>( &y.l() ),
        reinterpret_cast<size_t>( &z.l() ),
        //  edges
        reinterpret_cast<size_t>( &a.n() ),
        reinterpret_cast<size_t>( &b.n() ),
        reinterpret_cast<size_t>( &c.n() ),
        reinterpret_cast<size_t>( &x.n() ),
        reinterpret_cast<size_t>( &y.n() ),
        reinterpret_cast<size_t>( &z.n() ),
        //  verts
        reinterpret_cast<size_t>( &x.d() ),
        reinterpret_cast<size_t>( &a.o() ),
        reinterpret_cast<size_t>( &b.o() ),
        reinterpret_cast<size_t>( &c.o() )
      };

      Assert::AreEqual( 13u, expected.size() );

      auto actual = Collision_NS::Vert( z.sym() ).neighbourhood();
      Assert::AreEqual( expected.size(), actual.size(), L"size" );

      auto actualID = ids( actual );
      Assert::AreEqual( expected.size(), actualID.size(), L"size ids" );

      Assert::IsTrue( expected == actualID );
    }

	};
}