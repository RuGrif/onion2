#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
  TEST_CLASS( General )
	{
	public:
		
    TEST_METHOD( ref )
		{
      int i = 42;
      int j = 13;

      //  take i

      auto r = std::ref( i );

      Assert::AreEqual<int>( i, r );

      //  take j

      r = std::ref( j );

      Assert::AreEqual<int>( j, r );
      Assert::AreNotEqual<int>( i, r );
      
      Assert::AreEqual( 42, i );
      Assert::AreEqual( 13, j );

      r.get() = 0;

      Assert::AreEqual( 42, i );
      Assert::AreEqual( 0, j );
		}

    TEST_METHOD( unique_ptr )
    {
      std::unique_ptr<char> p;

      auto q = std::move( p );
    }

	};
}