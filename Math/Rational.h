#pragma once


#include "IntType.h"


namespace Math_NS
{
  template <typename Int>
  struct Rational
  {
    Int n;  //  nominator
    Int d;  //  denominator
  };


  template <typename Int>
  bool operator < ( const Rational<Int>& l, const Rational<Int>& r )
  {
    return Math_NS::prod( l.n, r.d ) < Math_NS::prod( r.n, l.d );
  }


  template <typename Int> auto makeRational( const Int& n, const Int& d ) { return Rational<Int>{ n, d }; }


  using RationalType = Rational<IntType>;
}