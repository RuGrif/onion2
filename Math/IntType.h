#pragma once
#include <boost/multiprecision/cpp_int.hpp>


//#define LOW_RES //  low resolution grid for debug purposes


namespace Math_NS
{
#ifdef LOW_RES
  using IntType = long long;  //  debug version
#else
  using IntType = boost::multiprecision::int256_t;
#endif
  
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

    //  debug version
    inline long long prod( long long x, long long y ) { return x * y; }
  }

  using IntTypeImpl_NS::prod;
}