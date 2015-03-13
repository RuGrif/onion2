#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Math\Vector3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS( Vector3 )
	{
	public:
		
		TEST_METHOD( Equal )
		{
      Assert::AreEqual( Math_NS::Vector3I( 1, 2, 3 ), Math_NS::Vector3I( 1, 2, 3 ) );
      Assert::AreNotEqual( Math_NS::Vector3I( 1, 2, 3 ), Math_NS::Vector3I() );
		}


    TEST_METHOD( Plus )
    {
      Assert::AreEqual( Math_NS::Vector3I( 5, 7, 9 ), Math_NS::Vector3I( 1, 2, 3 ) + Math_NS::Vector3I( 4, 5, 6 ) );
    }

    
    TEST_METHOD( Minus )
    {
      Assert::AreEqual( Math_NS::Vector3I( 1, 2, 3 ), Math_NS::Vector3I( 5, 7, 9 ) - Math_NS::Vector3I( 4, 5, 6 ) );
    }


    TEST_METHOD( ScalarProduct )
    {
      Assert::AreEqual( 10, Math_NS::Vector3I( 1, 2, 3 ) * Math_NS::Vector3I( 3, 2, 1 ) );
    }


    TEST_METHOD( VectorProduct )
    {
      Assert::AreEqual( Math_NS::Vector3I( 0, 0, 1 ), Math_NS::Vector3I( 1, 0, 0 ) ^ Math_NS::Vector3I( 0, 1, 0 ) );
      Assert::AreEqual( Math_NS::Vector3I( 1, 0, 0 ), Math_NS::Vector3I( 0, 1, 0 ) ^ Math_NS::Vector3I( 0, 0, 1 ) );
      Assert::AreEqual( Math_NS::Vector3I( 0, 1, 0 ), Math_NS::Vector3I( 0, 0, 1 ) ^ Math_NS::Vector3I( 1, 0, 0 ) );

      Assert::AreEqual( Math_NS::Vector3I( 0, 0, 0 ), Math_NS::Vector3I( 1, 2, 3 ) ^ Math_NS::Vector3I( 1, 2, 3 ) );
    }

    TEST_METHOD( Multiply )
    {
      Assert::AreEqual( Math_NS::Vector3I( 0, 2, 4 ), 2 * Math_NS::Vector3I( 0, 1, 2 ) );
      Assert::AreEqual( Math_NS::Vector3I( 0, 2, 4 ), Math_NS::Vector3I( 0, 1, 2 ) * 2 );
    }
	};
}