#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Math/Rational.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{    
  TEST_CLASS( Rational )
  {
  public:

    TEST_METHOD( SmallRational )
    {
      using namespace Math_NS;

      auto a = makeRational<IntType>( 1, 2 );
      auto b = makeRational<IntType>( 3, 4 );

      Assert::IsTrue( a < b );
    }

    TEST_METHOD( BigRational )
    {
      using namespace Math_NS;

      auto a = makeRational( std::numeric_limits<IntType>::max() - 4, std::numeric_limits<IntType>::max() - 3 );
      auto b = makeRational( std::numeric_limits<IntType>::max() - 2, std::numeric_limits<IntType>::max() - 1 );

      Assert::IsTrue( a < b );
    }
  };
}