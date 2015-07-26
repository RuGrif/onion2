#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\LongInt\LongInt.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using uli64 = LongInt_NS::LongIntRaw<uint32_t>;
using uli128 = LongInt_NS::LongIntRaw<uli64>;

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const uli64& i ) { return ToString( i.h ) + L'.' + ToString( i.l ); }
template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const uli128& i ) { return ToString( i.h ) + L'.' + ToString( i.l ); }


namespace UnitTest
{
  TEST_CLASS( LongInt64 )
  {
  public:

    //  no internal cary flag, no external cary flag
    TEST_METHOD( add00 )
    {
      uli64 i( 1u, 2u ), j( 4u, 8u );
      
      Assert::AreEqual( 0u, i.add( j ) );
      
      Assert::AreEqual( uli64{ 5u, 10u }, i );
      Assert::AreEqual( uli64{ 4u, 8u }, j );
    }

    //  internal flag only
    TEST_METHOD( add01 )
    {
      uli64 i( 42u, std::numeric_limits<uint32_t>::max() ), j( 13u, 1u );
      
      Assert::AreEqual( 0u, i.add( j ) );
      
      Assert::AreEqual( uli64{ 56u, 0u }, i );
      Assert::AreEqual( uli64{ 13u, 1u }, j );
    }

    //  external flag only
    TEST_METHOD( add10 )
    {
      uli64 i( std::numeric_limits<uint32_t>::max(), 42u ), j( 1u, 13u );
      
      Assert::AreEqual( 1u, i.add( j ) );

      Assert::AreEqual( uli64{ 0u, 55u }, i );
      Assert::AreEqual( uli64{ 1u, 13u }, j );
    }

    //  both external and internal
    TEST_METHOD( add11 )
    {
      uli64 i = std::numeric_limits<uint64_t>::max(), j = 42u;
      Assert::AreEqual( uli64{ std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max() }, i );
      Assert::AreEqual( uli64{ 0u, 42u }, j );

      Assert::AreEqual( 1u, i.add( j ) );

      Assert::AreEqual( uli64{ 0u, 41u }, i );
      Assert::AreEqual( uli64{ 0u, 42u }, j );
    }

    //  no internal cary flag, no external cary flag
    TEST_METHOD( sub00 )
    {
      uli64 i( 4u, 8u ), j( 1u, 2u );

      Assert::AreEqual( 0u, i.sub( j ) );

      Assert::AreEqual( uli64{ 3u, 6u }, i );
      Assert::AreEqual( uli64{ 1u, 2u }, j );
    }

    //  internal flag only
    TEST_METHOD( sub01 )
    {
      uli64 i( 42u, 0 ), j( 13u, 1u );

      Assert::AreEqual( 0u, i.sub( j ) );

      Assert::AreEqual( uli64{ 28u, std::numeric_limits<uint32_t>::max() }, i );
      Assert::AreEqual( uli64{ 13u, 1u }, j );
    }

    //  external flag only
    TEST_METHOD( sub10 )
    {
      uli64 i( 2u, 42u ), j( 3u, 13u );

      Assert::AreEqual( 1u, i.sub( j ) );

      Assert::AreEqual( uli64{ std::numeric_limits<uint32_t>::max(), 29u }, i );
      Assert::AreEqual( uli64{ 3u, 13u }, j );
    }

    //  both external and internal
    TEST_METHOD( sub11 )
    {
      uli64 i, j = 1u;

      Assert::AreEqual( 1u, i.sub( j ) );

      Assert::AreEqual( uli64{ std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max() }, i );
      Assert::AreEqual( uli64{ 0u, 1u }, j );
    }
  };
}