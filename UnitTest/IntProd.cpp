#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Math/IntType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
  using namespace boost::multiprecision;

  using std::to_string;

	TEST_CLASS( IntProd )
	{
    std::string tenpow( size_t pow )
    {
      std::string r( pow + 1, '0' );
      r[ 0 ] = '1';
      return r;
    }
	public:

		TEST_METHOD( Boost_int256 )
		{
      int256_t x = 10; //  expect int 256 ~ 10^77

      for( size_t p = 1; p < 78; ++p, x *= 10 )
      {
        Assert::AreEqual( tenpow( p ), x.str() );
      }
		}

    TEST_METHOD( MathNS_Prod )
    {
      using Math_NS::prod;

      auto i = []( size_t p ) { return pow( int256_t{ 10 }, p ); };

      auto i0 = i( 70 );
      auto i1 = i( 71 );
      auto i2 = i( 72 );
      auto i3 = i( 73 );

      auto i4 = i( 74 );
      auto i5 = i( 75 );
      auto i6 = i( 76 );
      auto i7 = i( 77 );

      Assert::AreEqual( tenpow( 70 ), i0.str() );
      Assert::AreEqual( tenpow( 71 ), i1.str() );
      Assert::AreEqual( tenpow( 72 ), i2.str() );
      Assert::AreEqual( tenpow( 73 ), i3.str() );
      
      Assert::AreEqual( tenpow( 74 ), i4.str() );
      Assert::AreEqual( tenpow( 75 ), i5.str() );
      Assert::AreEqual( tenpow( 76 ), i6.str() );
      Assert::AreEqual( tenpow( 77 ), i7.str() );

      auto j0 = prod( i0, i1 );
      auto j1 = prod( i2, i3 );
      auto j2 = prod( i4, i5 );
      auto j3 = prod( i6, i7 );
      
      Assert::AreEqual( tenpow( 70 + 71 ), j0.str() );
      Assert::AreEqual( tenpow( 72 + 73 ), j1.str() );
      Assert::AreEqual( tenpow( 74 + 75 ), j2.str() );
      Assert::AreEqual( tenpow( 76 + 77 ), j3.str() );

      auto k0 = prod( j0, j1 );
      auto k1 = prod( j2, j3 );

      Assert::AreEqual( tenpow( 70 + 71 + 72 + 73 ), k0.str() );
      Assert::AreEqual( tenpow( 74 + 75 + 76 + 77 ), k1.str() );

      auto x0 = prod( k0, k1 );

      Assert::AreEqual( tenpow( 70 + 71 + 72 + 73 + 74 + 75 + 76 + 77 ), x0.str() );
    }
	};
}