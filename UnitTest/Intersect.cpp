#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Math\Intersect.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( Intersect )
	{
    Math_NS::Point::Vec rot( Math_NS::Point::Vec v ) { return{ v.y, v.z, v.x }; }

	public:

    TEST_METHOD( VecRot )
    {
      Assert::AreEqual( Math_NS::Point::Vec( 2, 3, 1 ), rot( { 1, 2, 3 } ) );
    }
		
    TEST_METHOD( FaceEdge_Pos )
		{
      Math_NS::Point::Vec a( 0, 0, 0 );
      Math_NS::Point::Vec b( 1, 0, 0 );
      Math_NS::Point::Vec c( 0, 1, 0 );
      Math_NS::Point::Vec u( -1, 0, +1 );
      Math_NS::Point::Vec v( +1, 0, -1 );
      
      for( size_t i = 0; i < 3; ++i )
      {
        Math_NS::Point A( a = rot( a ) );
        Math_NS::Point B( b = rot( b ) );
        Math_NS::Point C( c = rot( c ) );
        Math_NS::Point U( u = rot( u ) );
        Math_NS::Point V( v = rot( v ) );

        Math_NS::Point::Int div = Math_NS::intersect( A, B, C, U, V );

        Assert::AreNotEqual( 0LL, div );

        Assert::AreEqual( div, U.weight() + V.weight() );
        Assert::AreEqual( div, A.weight() + B.weight() + C.weight() );

        Assert::AreEqual( *U + *V, *A + *B + *C );
        Assert::AreEqual( Math_NS::Point::Vec{}, *U + *V );
      }
		}

    TEST_METHOD( FaceEdge_Neg )
    {
      Math_NS::Point::Vec a( 0, 0, 0 );
      Math_NS::Point::Vec b( 3, 0, 0 );
      Math_NS::Point::Vec c( 0, 3, 0 );
      Math_NS::Point::Vec u( 1, 1, 0 );
      Math_NS::Point::Vec v( 3, 3, 0 );

      for( size_t i = 0; i < 3; ++i )
      {
        Math_NS::Point A( a = rot( a ) );
        Math_NS::Point B( b = rot( b ) );
        Math_NS::Point C( c = rot( c ) );
        Math_NS::Point U( u = rot( u ) );
        Math_NS::Point V( v = rot( v ) );

        Math_NS::Point::Int div = Math_NS::intersect( A, B, C, U, V );

        Assert::AreEqual( 0LL, div );
      }
    }

    TEST_METHOD( EdgeEdge_Pos )
    {
      Math_NS::Point::Vec a( 1, 0, 0 );
      Math_NS::Point::Vec b( 2, 0, 0 );
      Math_NS::Point::Vec u( 0, 1, 0 );
      Math_NS::Point::Vec v( 0, 2, 0 );

      for( size_t i = 0; i < 3; ++i )
      {
        Math_NS::Point A( a = rot( a ) );
        Math_NS::Point B( b = rot( b ) );
        Math_NS::Point U( u = rot( u ) );
        Math_NS::Point V( v = rot( v ) );

        Math_NS::Point::Int div = Math_NS::intersect( A, B, U, V );

        Assert::AreNotEqual( 0LL, div );

        Assert::AreEqual( div, U.weight() + V.weight() );
        Assert::AreEqual( div, A.weight() + B.weight() );

        Assert::AreEqual( *U + *V, *A + *B );
        Assert::AreEqual( Math_NS::Point::Vec{}, *U + *V );
      }
    }

    TEST_METHOD( EdgeEdge_Neg )
    {
      Math_NS::Point::Vec a( -1, 0, 0 );
      Math_NS::Point::Vec b( +1, 0, 0 );
      Math_NS::Point::Vec u( 0, -1, 1 );
      Math_NS::Point::Vec v( 0, +1, 1 );

      for( size_t i = 0; i < 3; ++i )
      {
        Math_NS::Point A( a = rot( a ) );
        Math_NS::Point B( b = rot( b ) );
        Math_NS::Point U( u = rot( u ) );
        Math_NS::Point V( v = rot( v ) );

        Math_NS::Point::Int div = Math_NS::intersect( A, B, U, V );

        Assert::AreEqual( 0LL, div );
      }
    }

    TEST_METHOD( VertEdge_Pos )
    {
      Math_NS::Point::Vec a( 0, 0, 0 );
      Math_NS::Point::Vec u( -1, 0, +2 );
      Math_NS::Point::Vec v( +1, 0, -2 );

      for( size_t i = 0; i < 3; ++i )
      {
        Math_NS::Point A( a = rot( a ) );
        Math_NS::Point U( u = rot( u ) );
        Math_NS::Point V( v = rot( v ) );

        Math_NS::Point::Int div = Math_NS::intersect( A, U, V );

        Assert::AreNotEqual( 0LL, div );

        Assert::AreEqual( div, U.weight() + V.weight() );
        Assert::AreEqual( div, A.weight() );

        Assert::AreEqual( *U + *V, *A );
        Assert::AreEqual( Math_NS::Point::Vec{}, *U + *V );
      }
    }

    TEST_METHOD( VertEdge_Neg )
    {
      Math_NS::Point::Vec a( 0, 1, 0 );
      Math_NS::Point::Vec u( -1, 0, +2 );
      Math_NS::Point::Vec v( +1, 0, -2 );

      for( size_t i = 0; i < 3; ++i )
      {
        Math_NS::Point A( a = rot( a ) );
        Math_NS::Point U( u = rot( u ) );
        Math_NS::Point V( v = rot( v ) );

        Math_NS::Point::Int div = Math_NS::intersect( A, U, V );

        Assert::AreEqual( 0LL, div );
      }
    }
	};
}