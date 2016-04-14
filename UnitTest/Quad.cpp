#include "stdafx.h"
#include "CppUnitTest.h"
#include "../QEdge/Quad.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( Quad )
  {
    template <typename T>
    void testEdgeTopology( QEdge_NS::Loop<T>& e )
    {
      {
        Assert::AreNotSame( e, e.dual().dual(), L"rot^2" ); //-V807
        Assert::AreSame( e, e.dual().dual().dual().dual(), L"rot^4" );
      }

      {
        auto& o = e;
        Assert::AreSame( o, o.next(), L"O-ring" );
      }

      {
        auto& o = e.dual().dual();
        Assert::AreSame( o, o.next(), L"D-ring" );
      }

      {
        auto& o = e.dual();
        Assert::AreSame( o.dual().dual(), o.next(), L"R-ring-1" );
        Assert::AreSame( o, o.next().next(), L"R-ring-2" );
      }

      {
        auto& o = e.dual().dual().dual();
        Assert::AreSame( o.dual().dual(), o.next(), L"L-ring-1" );
        Assert::AreSame( o, o.next().next(), L"L-ring-2" );
      }
    }

    template <typename T>
    void testEdgeData( QEdge_NS::Loop<T>& e )
    {
      Assert::AreNotSame( e.vert(), e.dual().dual().vert() );
      Assert::AreSame( e.dual().vert(), e.dual().dual().dual().vert() );
    }

    template <typename T>
    void testFuse( QEdge_NS::Loop<T>& e )
    {
      testEdgeTopology( e );
      testEdgeData( e );

      e.fuse0( e.dual().dual() );

      Assert::AreNotSame( e, e.next() );
      Assert::AreSame( e.next(), e.dual().dual() );

      e.fuse1( e.dual().dual() );

      testEdgeTopology( e );
      testEdgeData( e );
    }

  public:
    
    TEST_METHOD( EdgeRings )
    {
      QEdge_NS::Quad q{ QEdge_NS::Quad::Edge{} };

      testEdgeTopology( q.edge() );
    }

    TEST_METHOD( LoopRings )
    {
      QEdge_NS::Quad q{ QEdge_NS::Quad::Loop{} };

      testEdgeTopology( q.edge().dual() );
    }

    TEST_METHOD( EdgeFuse )
    {
      QEdge_NS::Quad q( QEdge_NS::Quad::Edge{} );

      testFuse( q.edge() );
    }

    TEST_METHOD( FaceFuse )
    {
      QEdge_NS::Quad q( QEdge_NS::Quad::Loop{} );

      testFuse( q.edge().dual() );
    }

  };
}