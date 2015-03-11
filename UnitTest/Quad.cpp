#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\QEdge\Quad.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( Quad )
	{
	public:
		
		TEST_METHOD( EdgeRings )
		{
      QEdge_NS::Quad q{ QEdge_NS::Quad::Edge{} };

      auto& e = q.edge();

      {
        Assert::AreNotSame( e, e.dual().dual(), L"rot^2" );
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

    TEST_METHOD( LoopRings )
    {
      QEdge_NS::Quad q{ QEdge_NS::Quad::Loop{} };

      auto& e = q.edge().dual();

      {
        Assert::AreNotSame( e, e.dual().dual(), L"rot^2" );
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

	};
}