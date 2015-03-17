#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Math\Box3.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Box3 )
	{
	public:
		
    TEST_METHOD( Box )
		{
      Math_NS::Box3I b;

      Assert::IsTrue( b.empty() );

      b += Math_NS::Vector3I{};

      Assert::AreEqual( Math_NS::Vector3I( 0, 0, 0 ), b.min );
      Assert::AreEqual( Math_NS::Vector3I( 0, 0, 0 ), b.max );

      Assert::IsFalse( b.empty() );
      Assert::AreEqual( 0, b.volume() );

      b += Math_NS::Vector3I{ 2, 2, 2 };

      Assert::AreEqual( Math_NS::Vector3I( 0, 0, 0 ), b.min );
      Assert::AreEqual( Math_NS::Vector3I( 2, 2, 2 ), b.max );

      Assert::IsFalse( b.empty() );
      Assert::AreEqual( 8, b.volume() );

      b = b + Math_NS::Box3I( Math_NS::Vector3I( 1, 1, 1 ), Math_NS::Vector3I( 3, 3, 3 ) );

      Assert::AreEqual( Math_NS::Vector3I( 0, 0, 0 ), b.min );
      Assert::AreEqual( Math_NS::Vector3I( 3, 3, 3 ), b.max );

      b += Math_NS::Box3I( Math_NS::Vector3I( -1, -2, -3 ), Math_NS::Vector3I( 3, 3, 3 ) );

      Assert::AreEqual( Math_NS::Vector3I( -1, -2, -3 ), b.min );
      Assert::AreEqual( Math_NS::Vector3I( 3, 3, 3 ), b.max );
		}

	};
}