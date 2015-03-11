#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS( SpliceTopology )
	{
    //  isolated edge
    void checkTopology( QEdge_NS::Edge e )
    {
      Assert::AreEqual( e, e.oNext(), L"o.next == e" );
      Assert::AreEqual( e, e.oPrev(), L"o.prev == e" );
      Assert::AreEqual( e, e.dNext(), L"d.next == e" );
      Assert::AreEqual( e, e.dPrev(), L"d.prev == e" );

      Assert::AreSame( e.l(), e.r(), L"l == r" );
      Assert::AreNotSame( e.o(), e.d(), L"o != d" );
    }

    //  Vert loop a -> b -> a
    void checkTopology( QEdge_NS::Edge a, QEdge_NS::Edge b )
    {
      Assert::AreNotEqual( a, b, L"a != b" );

      Assert::AreEqual( b, a.oNext(), L"a.next == b" );
      Assert::AreEqual( b, a.oPrev(), L"a.prev == b" );
      Assert::AreEqual( a, b.oNext(), L"b.next == a" );
      Assert::AreEqual( a, b.oPrev(), L"b.prev == a" );

      Assert::AreEqual( a, a.dNext(), L"a.sym.next == a" );
      Assert::AreEqual( a, a.dPrev(), L"a.sym.prev == a" );
      Assert::AreEqual( b, b.dNext(), L"b.sym.next == b" );
      Assert::AreEqual( b, b.dPrev(), L"b.sym.prev == b" );

      Assert::AreSame( a.l(), a.r(), L"face loop (a)" );
      Assert::AreSame( b.l(), b.r(), L"face loop (b)" );
      Assert::AreSame( a.l(), b.l(), L"face loop (ab)" );

      Assert::AreNotSame( a.d(), a.o(), L"vert loop (a.d != o)" );
      Assert::AreNotSame( b.d(), a.o(), L"vert loop (b.d != o)" );
      Assert::AreNotSame( a.d(), b.d(), L"vert loop (a.d != b.d)" );

      Assert::AreSame( a.o(), b.o(), L"vert loop (o)" );
    }

	public:

    TEST_METHOD( Splice0 )
    {
      QEdge_NS::Shape s;

      QEdge_NS::Edge a = s.makeEdge();
      QEdge_NS::Edge b = s.makeEdge();

      label( a, L"a" );
      label( b, L"b" );

      //
      //  merge a.o and b.o
      //

      a.splice0( b );

      checkTopology( a, b );
    }

    TEST_METHOD( Splice1 )
    {
      QEdge_NS::Shape s;

      QEdge_NS::Edge a = s.makeEdge();
      QEdge_NS::Edge b = s.makeEdge();

      label( a, L"a" );
      label( b, L"b" );

      //
      //  merge a.o and b.o
      //

      a.splice1( b );

      checkTopology( a, b );
    }

    TEST_METHOD( SpliceX2 )
    {
      QEdge_NS::Shape s;

      QEdge_NS::Edge a = s.makeEdge();
      QEdge_NS::Edge b = s.makeEdge();

      label( a, L"a" );
      label( b, L"b" );

      //
      //  attach/detach a.o and b.o
      //

      checkTopology( a );
      checkTopology( b );

      for( auto ee1 : { std::make_pair( a, b ), std::make_pair( b, a ) } )
      {
        for( auto s1 : { &QEdge_NS::Edge::splice0, &QEdge_NS::Edge::splice1 } )
        {
          for( auto ee2 : { std::make_pair( a, b ), std::make_pair( b, a ) } )
          {
            for( auto s2 : { &QEdge_NS::Edge::splice0, &QEdge_NS::Edge::splice1 } )
            {
              ( ee1.first.*s1 )( ee1.second );
              
              checkTopology( a, b );
              
              ( ee2.first.*s2 )( ee2.second );
              
              checkTopology( a );
              checkTopology( b );
            }
          }
        }
      }
    }

	};

  TEST_CLASS( SpliceData )
  {
  public:

    TEST_METHOD( Splice0 )
    {
      QEdge_NS::Shape s;

      QEdge_NS::Edge a = s.makeEdge();
      QEdge_NS::Edge b = s.makeEdge();

      label( a, L"a" );
      label( b, L"b" );

      //
      //  preserve a.o and a.l loops
      //

      auto o = a.o()->tag();
      auto l = a.l()->tag();

      Assert::AreNotEqual( o, b.o()->tag() );
      Assert::AreNotEqual( l, b.l()->tag() );

      a.splice0( b );

      Assert::IsTrue( a.o() );
      Assert::IsTrue( b.o() );

      Assert::AreEqual( o, a.o()->tag() );
      Assert::AreEqual( o, b.o()->tag() );

      Assert::IsTrue( a.l() );
      Assert::IsTrue( b.l() );

      Assert::AreEqual( l, a.l()->tag() );
      Assert::AreEqual( l, b.l()->tag() );

      a.splice0( b );

      Assert::IsTrue( a.o() );
      Assert::IsFalse( b.o() );

      Assert::AreEqual( o, a.o()->tag() );
      
      Assert::IsTrue( a.l() );
      Assert::IsFalse( b.l() );

      Assert::AreEqual( l, a.l()->tag() );
    }

    TEST_METHOD( Splice1 )
    {
      QEdge_NS::Shape s;

      QEdge_NS::Edge a = s.makeEdge();
      QEdge_NS::Edge b = s.makeEdge();

      label( a, L"a" );
      label( b, L"b" );

      //
      //  preserve a.o and b.l loops
      //

      auto o = a.o()->tag();
      auto l = b.l()->tag();

      Assert::AreNotEqual( o, b.o()->tag() );
      Assert::AreNotEqual( l, a.l()->tag() );

      a.splice1( b );

      Assert::IsTrue( a.o() );
      Assert::IsTrue( b.o() );

      Assert::AreEqual( o, a.o()->tag() );
      Assert::AreEqual( o, b.o()->tag() );

      Assert::IsTrue( a.l() );
      Assert::IsTrue( b.l() );

      Assert::AreEqual( l, a.l()->tag() );
      Assert::AreEqual( l, b.l()->tag() );

      a.splice1( b );

      Assert::IsTrue( a.o() );
      Assert::IsFalse( b.o() );

      Assert::AreEqual( o, a.o()->tag() );

      Assert::IsFalse( a.l() );
      Assert::IsTrue( b.l() );

      Assert::AreEqual( l, b.l()->tag() );
    }
  };
}