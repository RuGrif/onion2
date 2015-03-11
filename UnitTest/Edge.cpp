#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Edge )
	{
	public:

    TEST_METHOD( Label )
    {
      QEdge_NS::Shape s;

      {
        QEdge_NS::Edge e = s.makeEdge();

        label( e, L"e" );

        Assert::AreEqual<std::wstring>( L"e.o", e.o()->tag() );
        Assert::AreEqual<std::wstring>( L"e.d", e.d()->tag() );
        Assert::AreEqual<std::wstring>( L"e.l", e.l()->tag() );
        Assert::AreEqual<std::wstring>( L"e.l", e.r()->tag() );
      }

      {
        QEdge_NS::Edge e = s.makeLoop();

        label( e, L"e" );

        Assert::AreEqual<std::wstring>( L"e.o", e.o()->tag() );
        Assert::AreEqual<std::wstring>( L"e.o", e.d()->tag() );
        Assert::AreEqual<std::wstring>( L"e.l", e.l()->tag() );
        Assert::AreEqual<std::wstring>( L"e.r", e.r()->tag() );
      }
    }

    TEST_METHOD( EmptyEdge )
    {
      QEdge_NS::Edge e;
      Assert::IsFalse( e );

      QEdge_NS::Edge c = e;
      Assert::IsFalse( c );

      Assert::IsFalse( c = e );
    }

    TEST_METHOD( NonEmptyEdge )
    {
      QEdge_NS::Shape s;

      QEdge_NS::Edge e = s.makeEdge();

      Assert::IsTrue( e );

      QEdge_NS::Edge c = e;
      Assert::IsTrue( c );

      Assert::IsTrue( c = e );
    }
		
    TEST_METHOD( EdgeNavigation )
		{
      QEdge_NS::Shape s;
      QEdge_NS::Edge e = s.makeEdge();

      label( e, L"edge" );

      Assert::AreEqual( e, e.oNext(), L"oNext" );
      Assert::AreEqual( e, e.oPrev(), L"oPrev" );
      Assert::AreEqual( e, e.dNext(), L"dNext" );
      Assert::AreEqual( e, e.dPrev(), L"dPrev" );

      Assert::AreNotEqual( e, e.sym(), L"sym" );
      Assert::AreEqual( e, e.sym().sym(), L"sym^2" );

      Assert::AreEqual( e.sym(), e.lNext(), L"lNext" );
      Assert::AreEqual( e.sym(), e.lPrev(), L"lPrev" );
      Assert::AreEqual( e.sym(), e.rNext(), L"rNext" );
      Assert::AreEqual( e.sym(), e.rPrev(), L"rPrev" );
		}

    TEST_METHOD( LoopNavigation )
    {
      QEdge_NS::Shape s;
      QEdge_NS::Edge e = s.makeLoop();

      label( e, L"loop" );

      Assert::AreEqual( e.sym(), e.oNext(), L"oNext" );
      Assert::AreEqual( e.sym(), e.oPrev(), L"oPrev" );
      Assert::AreEqual( e.sym(), e.dNext(), L"dNext" );
      Assert::AreEqual( e.sym(), e.dPrev(), L"dPrev" );

      Assert::AreNotEqual( e, e.sym(), L"sym" );
      Assert::AreEqual( e, e.sym().sym(), L"sym^2" );

      Assert::AreEqual( e, e.lNext(), L"lNext" );
      Assert::AreEqual( e, e.lPrev(), L"lPrev" );
      Assert::AreEqual( e, e.rNext(), L"rNext" );
      Assert::AreEqual( e, e.rPrev(), L"rPrev" );
    }
	};
}