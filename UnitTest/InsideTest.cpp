#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Triangulation/InsideTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{    
  using namespace Triangulation_NS;
  using Int = Math_NS::IntType;

  TEST_CLASS( InsideTest )
  {
    auto makePoint1( Int x, Int y, Int d ) { return makePoint( x, y, d ); }
    auto makePoint2( Int x, Int y, Int d ) { return makePoint( y,-x, d ); }
    auto makePoint3( Int x, Int y, Int d ) { return makePoint(-x,-y, d ); }
    auto makePoint4( Int x, Int y, Int d ) { return makePoint(-y, x, d ); }

    void test( const Point& a, const Point& b, const Point& p )
    {
      Assert::IsTrue ( isAtLeftSide( a, b, p ) );
      Assert::IsFalse( isAtLeftSide( b, a, p ) );
    }

    void test(
      Int ax, Int ay, Int ad,
      Int bx, Int by, Int bd,
      Int px, Int py, Int pd )
    {
      test( makePoint1( ax, ay, ad ), makePoint1( bx, by, bd ), makePoint1( px, py, pd ) );
      test( makePoint2( ax, ay, ad ), makePoint2( bx, by, bd ), makePoint2( px, py, pd ) );
      test( makePoint3( ax, ay, ad ), makePoint3( bx, by, bd ), makePoint3( px, py, pd ) );
      test( makePoint4( ax, ay, ad ), makePoint4( bx, by, bd ), makePoint4( px, py, pd ) );
    }

  public:

    TEST_METHOD( IsAtLeftSide )
    {
      test(
        0, 0, 1,
        1, 0, 1,
        0, 1, 1 );

      test(
        1, 1, 9,
        1, 1, 8,
        7, 8, 7 );

      test(
        1, 2, 9,
        8,-1, 7,
        3, 9, 2 );
    }
  };
}