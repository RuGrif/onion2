#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Tailor/FaceCCW.h"
#include <vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{		
  const int sum = 1000;

  struct Pos { int x, y; };

  Pos operator + ( const Pos& a, const Pos& b ) { return{ a.x + b.x, a.y + b.y }; }

  Collision_NS::BaryF makePoint( int x, int y )
  {
    Assert::IsTrue( 0 <= x, L"x" );
    Assert::IsTrue( 0 <= y, L"x" );
    Assert::IsTrue( x + y <= sum, L"z" );

    return{ x, y, sum - x - y };
  }

  Collision_NS::BaryF makePoint( Pos p ) { return makePoint( p.x, p.y ); }

  struct MyCCW
  {
    Tailor_NS::FaceCCW ccw;
    Pos                       ref;
    
    MyCCW( const Pos& o ) : ref{ o }, ccw{ makePoint( o ) } {}

    bool compare( const Pos& a, const Pos& b )
    {
      return ccw( makePoint( ref + a ), makePoint( ref + b ) );
    }
  };

	TEST_CLASS( FaceCCW )
	{
	public:

		TEST_METHOD( NoOffset )
		{
      MyCCW c{ { 0, 0 } };

      Assert::IsTrue( c.compare( { 2, 1 }, { 1, 2 } ) );
		}

    TEST_METHOD( ByAngle )
    {
      MyCCW c{ { 200, 200 } };

      auto circle = []( double A )
      {
        return Pos{ static_cast<int>( ::round( 100 * ::cos( A ) ) ), static_cast<int>( ::round( 100 * ::sin( A ) ) ) };
      };

      int n = 32;
      for( int i = 0; i + 1 < n; ++i )
      {
        const double pi = 3.1415926535897932384626433832795;
        
        double A0 = pi * i / n;
        double A1 = pi * ( i + 1 ) / n;

        Assert::IsTrue( c.compare( circle( A0 ), circle( A1 ) ) );
      }
    }

    TEST_METHOD( ByRadius )
    {
      MyCCW c{ { 200, 200 } };

      Assert::IsTrue( c.compare( { 1, 1 }, { 2, 2 } ) );
      Assert::IsTrue( c.compare( {-1, 1 }, {-2, 2 } ) );
      Assert::IsTrue( c.compare( { 1,-1 }, { 2,-2 } ) );
      Assert::IsTrue( c.compare( {-1,-1 }, {-2,-2 } ) );
    }

    TEST_METHOD( Overturn )
    {
      MyCCW c{ { 200, 200 } };

      Assert::IsFalse( c.compare( { 100,-1 }, { 100, 1 } ) );
    }

    TEST_METHOD( Combined )
    {
      MyCCW cmp{ { 200, 200 } };

      Pos a{ 11, 10 }, b{ 10, 10 }, c{ 11, 11 }, d{ 10, 11 };

      //  a < b < c < d;
      Assert::IsTrue( cmp.compare( a, b ), L"a < b" );
      Assert::IsTrue( cmp.compare( b, c ), L"b < c" );
      Assert::IsTrue( cmp.compare( c, d ), L"c < d" );
      Assert::IsFalse( cmp.compare( d, a ), L"d > a" );
    }
	};
}