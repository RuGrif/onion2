#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Math\Intersect.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  struct Counter
  {
    size_t counter = 0;
    static size_t total;

    Counter() { total = 0; } //  reset

    void count() { ++counter; ++total; }
  };

  size_t Counter::total = 0;

  struct VE : public Math_NS::VertEdge, public Counter
  {
    Vec vA;
    Vec vU, vV;

    VE( Vec vA, Vec vU, Vec vV ) : vA( vA ), vU( vU ), vV( vV ) {}

    virtual void operator() ( Int u, Int v, Int div ) override
    {
      count();

      Assert::IsTrue( div > 0 );
      Assert::AreEqual( u * vU + v * vV, div * vA, L"VE" );
    }
  };


  struct EE : public Math_NS::EdgeEdge, public Counter
  {
    Vec vA, vB;
    Vec vU, vV;
    VE d_A, d_B;

    EE( Vec vA, Vec vB, Vec vU, Vec vV )
      : vA( vA ), vB( vB ), vU( vU ), vV( vV )
      , d_A( vA, vU, vV ), d_B( vB, vU, vV )
    {}

    virtual void operator() ( Int a, Int b, Int u, Int v, Int div ) override
    {
      count();

      Assert::IsTrue( div > 0 );
      Assert::AreEqual( u * vU + v * vV, a * vA + b * vB, L"EE" );
    }

    virtual VE& A() override { return d_A; }
    virtual VE& B() override { return d_B; };
  };


  struct FE : public Math_NS::FaceEdge, public Counter
  {
    Vec vA, vB, vC;
    Vec vU, vV;
    EE d_AB, d_BC, d_CA;

    FE( Vec vA, Vec vB, Vec vC, Vec vU, Vec vV )
      : vA( vA ), vB( vB ), vC( vC ), vU( vU ), vV( vV )
      , d_AB( vA, vB, vU, vV ), d_BC( vB, vC, vU, vV ), d_CA( vC, vA, vU, vV )
    {}

    virtual void operator() ( Int a, Int b, Int c, Int u, Int v, Int div ) override
    {
      count();

      Assert::IsTrue( div > 0 );
      Assert::AreEqual( u * vU + v * vV, a * vA + b * vB + c * vC, L"FE" );
    }

    virtual EE& AB() override { return d_AB; }
    virtual EE& BC() override { return d_BC; }
    virtual EE& CA() override { return d_CA; }
  };


  TEST_CLASS( Intersect )
	{
	public:
		
    TEST_METHOD( FaceEdgeNormal )
		{
      Math_NS::IS_NS::Vec A( 0, 0, 0 );
      Math_NS::IS_NS::Vec B( 3, 0, 0 );
      Math_NS::IS_NS::Vec C( 0, 3, 0 );
      Math_NS::IS_NS::Vec U( 1, 1, +1 );
      Math_NS::IS_NS::Vec V( 1, 1, -1 );

      FE fe( A, B, C, U, V );

      Math_NS::intersect( A, B, C, U, V, fe );

      Assert::AreEqual( 1u, fe.counter );
      Assert::AreEqual( 1u, Counter::total );
		}

    TEST_METHOD( FaceEdge2EdgeEdge )
    {
      Math_NS::IS_NS::Vec A( 0, 0, 0 );
      Math_NS::IS_NS::Vec B( 3, 0, 0 );
      Math_NS::IS_NS::Vec C( 0, 3, 0 );
      Math_NS::IS_NS::Vec U( 1, 0, +1 );
      Math_NS::IS_NS::Vec V( 1, 0, -1 );

      FE fe( A, B, C, U, V );

      Math_NS::intersect( A, B, C, U, V, fe );

      Assert::AreEqual( 1u, fe.d_AB.counter );
      Assert::AreEqual( 1u, Counter::total );
    }
	};
}