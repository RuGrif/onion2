#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Shape )
	{
	public:
		
    TEST_METHOD( Triangle )
		{
      QEdge_NS::Shape s;

      QEdge_NS::Edge a = s.makeEdge();
      QEdge_NS::Edge b = s.makeEdge();
      QEdge_NS::Edge c = s.makeEdge();

      a.o().reset<QEdge_NS::DebugData>( L"A" );
      b.o().reset<QEdge_NS::DebugData>( L"B" );
      c.o().reset<QEdge_NS::DebugData>( L"C" );

      a.l().reset<QEdge_NS::DebugData>( L"in" );
      b.r().reset<QEdge_NS::DebugData>( L"out" );

      Assert::IsTrue( a.o() );
      Assert::IsTrue( b.o() );
      Assert::IsTrue( c.o() );

      Assert::IsFalse( a.d() );
      Assert::IsFalse( b.d() );
      Assert::IsFalse( c.d() );

      Assert::IsTrue( a.l() );
      Assert::IsTrue( a.r() );

      Assert::IsTrue( b.l() );
      Assert::IsTrue( b.r() );

      Assert::IsFalse( c.l() );
      Assert::IsFalse( c.r() );

      //  a -> b -> c

      //  c.l = c.r = a.l = a.r
      a.splice0( c.sym() ); //  -c-> * -a->
      //  all faces are equal to 'in'
      b.splice1( a.sym() ); //  -c-> * -a-> * -b->
      //  'in' is inside, null is outside
      c.splice0( b.sym() );

      Assert::AreSame( a.o(), c.d() );
      Assert::AreSame( b.o(), a.d() );
      Assert::AreSame( c.o(), b.d() );

      Assert::IsTrue( a.o() );
      Assert::IsTrue( b.o() );
      Assert::IsTrue( c.o() );

      Assert::AreSame( a.l(), b.l() );
      Assert::AreSame( b.l(), c.l() );

      Assert::IsTrue( a.l() );

      Assert::AreSame( a.r(), b.r() );
      Assert::AreSame( b.r(), c.r() );

      Assert::IsFalse( a.r() );

      //  test vert value

      Assert::AreEqual<std::wstring>( L"A", a.o()->tag() );
      Assert::AreEqual<std::wstring>( L"B", b.o()->tag() );
      Assert::AreEqual<std::wstring>( L"C", c.o()->tag() );
      Assert::AreEqual<std::wstring>( L"in", a.l()->tag() );
		}


    TEST_METHOD( Node )
    {
      QEdge_NS::Shape s;

      QEdge_NS::Edge e = s.makeLoop();

      Assert::IsFalse( e.o() );

      e.o().reset<QEdge_NS::DebugData>();

      Assert::IsTrue( e.o() );

      QEdge_NS::Vert v;
      e.o().swap( v );

      Assert::IsFalse( e.o() );
      Assert::IsTrue( v );

      swap( v, e.o() );

      Assert::IsTrue( e.o() );
      Assert::IsFalse( v );
    }


    TEST_METHOD( Size )
    {
      QEdge_NS::Shape s;

      Assert::AreEqual( 0u, s.size() );

      s.makeEdge();

      Assert::AreEqual( 1u, s.size() );

      s.makeLoop();

      Assert::AreEqual( 2u, s.size() );
    }


    TEST_METHOD( MoveCtor )
    {
      QEdge_NS::Shape s;

      s.makeEdge();

      Assert::AreEqual( 1u, s.size() );

      QEdge_NS::Shape t = std::move( s );

      Assert::AreEqual( 0u, s.size() );
      Assert::AreEqual( 1u, t.size() );
    }


    TEST_METHOD( MoveAssign )
    {
      QEdge_NS::Shape s, t;

      s.makeEdge();

      Assert::AreEqual( 1u, s.size() );
      Assert::AreEqual( 0u, t.size() );

      t = std::move( s );

      Assert::AreEqual( 0u, s.size() );
      Assert::AreEqual( 1u, t.size() );
    }
	};
}