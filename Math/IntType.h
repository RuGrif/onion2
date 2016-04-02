#pragma once
#include <boost/multiprecision/cpp_int.hpp>


namespace Math_NS
{
  using IntType = boost::multiprecision::int256_t;
}


namespace Math_NS
{
  namespace IntTypeImpl_NS
  {
    using namespace boost::multiprecision;

    template <size_t Base>
    auto prod(
      const number<cpp_int_backend<Base, Base, signed_magnitude, unchecked, void>>& x,
      const number<cpp_int_backend<Base, Base, signed_magnitude, unchecked, void>>& y )
    {
      number<cpp_int_backend<2u * Base, 2u * Base, signed_magnitude, unchecked, void>> r;
      return multiply( r, x, y );
    }
  }

  using IntTypeImpl_NS::prod;
}