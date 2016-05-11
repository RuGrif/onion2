#include "stdafx.h"
#include "CppUnitTest.h"
#include <boost/multiprecision/gmp.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{    
  TEST_CLASS( GMP )
  {
    using Int = boost::multiprecision::number<boost::multiprecision::gmp_int>;
    using Rational = boost::multiprecision::number<boost::multiprecision::gmp_rational>;

  public:

    TEST_METHOD( LongInt )
    {
      Int a0 = 14159265358979323LL;
      Int a1 = 84626433832795028LL;
      Int a2 = 84197169399375105LL;
      Int a3 = 82097494459230781LL;

      Int c = a0 * a1 * a2 * a3;

      Assert::AreEqual<std::string>( "8282742413512667515928436144968195998186106572106757733039556738220", c.str() );
    }

    TEST_METHOD( LongRational )
    {
      Rational a{ 1, 2 };
      Rational b{ 1, 3 };

      Assert::IsTrue( Rational{ 5, 6 } == a + b );
      Assert::IsTrue( Rational{ 1, 6 } == a - b );
      Assert::IsTrue( Rational{ 1, 6 } == a * b );
      Assert::IsTrue( Rational{ 3, 2 } == a / b );
    }
  };
}