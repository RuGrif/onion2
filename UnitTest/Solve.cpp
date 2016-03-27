#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Math\Solve.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( Solve )
	{
    Math_NS::Vector3L rot( const Math_NS::Vector3L& v ) { return{ v.y, v.z, v.x }; }

	public:
		
    TEST_METHOD( Solve_ABC_Pos )
		{
      Math_NS::Vector3L::Type a0 = 1, b0 = 2, c0 = 3;
      Math_NS::Vector3L A( 1, 2, 3 );
      Math_NS::Vector3L B( 0, 4, 5 );
      Math_NS::Vector3L C( 0, 0, 7 );
      Math_NS::Vector3L R = a0 * A + b0 * B + c0 * C;

      for( size_t i = 0; i < 3; ++i )
      {
        A = rot( A );
        B = rot( B );
        C = rot( C );
        R = rot( R );

        Math_NS::Vector3L::Type a, b, c;

        auto div = Math_NS::solve( A, B, C, R, a, b, c );

        Assert::AreNotEqual<Math_NS::Vector3L::Type>( 0, div );

        Assert::AreEqual( div * R, a * A + b * B + c * C );

        Assert::AreEqual( a0 * div, a );
        Assert::AreEqual( b0 * div, b );
        Assert::AreEqual( c0 * div, c );
      }
		}


    TEST_METHOD( Solve_ABC_Neg )
    {
      Math_NS::Vector3L::Type a0 = 1, b0 = 2, c0 = 3;
      Math_NS::Vector3L A( 1, 0, 0 );
      Math_NS::Vector3L B( 0, 1, 0 );
      Math_NS::Vector3L C( 1, 1, 0 );
      Math_NS::Vector3L R = a0 * A + b0 * B + c0 * C;

      for( size_t i = 0; i < 3; ++i )
      {
        A = rot( A );
        B = rot( B );
        C = rot( C );
        R = rot( R );

        Math_NS::Vector3L::Type a, b, c;

        auto div = Math_NS::solve( A, B, C, R, a, b, c );

        Assert::AreEqual<Math_NS::Vector3L::Type>( 0, div );
      }
    }


    TEST_METHOD( Solve_AB_Pos )
    {
      Math_NS::Vector3L::Type a0 = 3, b0 = -2;
      Math_NS::Vector3L A( 1, 2, 3 );
      Math_NS::Vector3L B( 0, 4, 5 );
      Math_NS::Vector3L R = a0 * A + b0 * B;

      for( size_t i = 0; i < 3; ++i )
      {
        A = rot( A );
        B = rot( B );
        R = rot( R );

        Math_NS::Vector3L::Type a, b;

        auto div = Math_NS::solve( A, B, R, a, b );

        Assert::AreNotEqual<Math_NS::Vector3L::Type>( 0, div );

        Assert::AreEqual( div * R, a * A + b * B );

        Assert::AreEqual( a0 * div, a );
        Assert::AreEqual( b0 * div, b );
      }
    }


    TEST_METHOD( Solve_AB_Neg )
    {
      Math_NS::Vector3L::Type a0 = 1, b0 = 2, c0 = 3;
      Math_NS::Vector3L A( 1, 0, 0 );
      Math_NS::Vector3L B( 0, 1, 0 );
      Math_NS::Vector3L C( 0, 0, 1 );
      Math_NS::Vector3L R = a0 * A + b0 * B + c0 * C;

      for( size_t i = 0; i < 3; ++i )
      {
        A = rot( A );
        B = rot( B );
        R = rot( R );

        Math_NS::Vector3L::Type a, b;

        auto div = Math_NS::solve( A, B, R, a, b );

        Assert::AreEqual<Math_NS::Vector3L::Type>( 0, div );
      }
    }


    TEST_METHOD( Solve_A_Pos )
    {
      Math_NS::Vector3L::Type a0 = 3;
      Math_NS::Vector3L A( 1, 2, 3 );
      Math_NS::Vector3L R = a0 * A;

      for( size_t i = 0; i < 3; ++i )
      {
        A = rot( A );
        R = rot( R );

        Math_NS::Vector3L::Type a;

        auto div = Math_NS::solve( A, R, a );

        Assert::AreNotEqual<Math_NS::Vector3L::Type>( 0, div );

        Assert::AreEqual( div * R, a * A );

        Assert::AreEqual( a0 * div, a );
      }
    }


    TEST_METHOD( Solve_A_Neg )
    {
      Math_NS::Vector3L::Type a0 = 1, b0 = 2;
      Math_NS::Vector3L A( 1, 0, 0 );
      Math_NS::Vector3L B( 0, 1, 0 );
      Math_NS::Vector3L R = a0 * A + b0 * B;

      for( size_t i = 0; i < 3; ++i )
      {
        A = rot( A );
        R = rot( R );

        Math_NS::Vector3L::Type a;

        auto div = Math_NS::solve( A, R, a );

        Assert::AreEqual<Math_NS::Vector3L::Type>( 0, div );
      }
    }

	};
}