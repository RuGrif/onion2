#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( Iterator )
  {
  public:
    
    TEST_METHOD( CountEdges )
    {
      QEdge_NS::Shape s;

      const size_t n = 42;

      for( size_t i = 0; i < n; ++i )
      {
        ( i * i ) % 7 <= 3 ? s.makeEdge() : s.makeLoop();
      }

      size_t c = 0;

      for( QEdge_NS::Edge e : s )
      {
        ++c;
      }

      Assert::AreEqual( n, c );
    }


    TEST_METHOD( Compare )
    {
      QEdge_NS::Shape s;

      Assert::IsTrue( s.begin() == s.end() );
      Assert::IsTrue( s.begin() == s.begin() ); //-V501
      Assert::IsTrue( s.end() == s.end() ); //-V501

      s.makeEdge();

      Assert::IsTrue( s.begin() != s.end() );
      Assert::IsTrue( std::next( s.begin() ) == s.end() );
      Assert::IsTrue( s.begin() == std::prev( s.end() ) );

      QEdge_NS::Iterator i;

      i = s.begin();

      Assert::IsTrue( i == i ); //-V501
      Assert::IsTrue( i == s.begin() );
      Assert::IsTrue( i != s.end() );

      ++i;

      Assert::IsTrue( i == i ); //-V501
      Assert::IsTrue( i != s.begin() );
      Assert::IsTrue( i == s.end() );
    }


    //  iterators are still valid if ones make a new edge/loop
    TEST_METHOD( Stability )
    {
      QEdge_NS::Shape s;

      auto e = s.end();

      Assert::AreEqual( 0, std::distance( s.begin(), e ) );

      s.makeEdge();

      Assert::AreEqual( 1, std::distance( s.begin(), e ) );

      //  take edge in the middle of edge construction

      for( size_t i = 0; i < 5; ++i ) s.makeEdge();

      e = std::next( s.begin(), 2 );
      Assert::IsFalse( e == s.end() );

      auto& o = e->o(); //  take the vertex as well

      for( size_t i = 0; i < 7; ++i ) s.makeEdge();

      //  check the edge is still good

      Assert::IsFalse( e == s.end() );

      Assert::AreEqual<int>( s.size(), std::distance( s.begin(), e ) + std::distance( e, s.end() ) );

      Assert::AreSame( o, e->o() );
    }

    TEST_METHOD( EdgeAccess )
    {
      QEdge_NS::Shape s;

      QEdge_NS::Edge e = s.makeLoop();

      label( e, L"e" );

      QEdge_NS::Iterator i = s.begin();

      Assert::AreEqual( e, *i );
    }


    TEST_METHOD( NotShared )
    {
      QEdge_NS::Shape s;

      for( size_t i = 0; i < 5; ++i ) s.makeLoop();

      auto i = std::next( s.begin(), 2 );
      auto j = i;

      Assert::IsTrue( i == j );

      ++i;

      Assert::IsTrue( i != j );

      ++j;

      Assert::IsTrue( i == j );
    }

  };
}