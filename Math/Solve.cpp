#include "Solve.h"

namespace
{
  using Vec = Math_NS::Vector3L;
  using Int = Vec::Type;
}


Int Math_NS::solve(
  const Vec& A,
  const Vec& B,
  const Vec& C,
  const Vec& R,
  Int& a,
  Int& b,
  Int& c )
{
  auto det = []( const Vec& A, const Vec& B, const Vec& C ) { return ( A ^ B ) * C; };

  if( auto div = det( A, B, C ) )
  {
    a = det( R, B, C );
    b = det( A, R, C );
    c = det( A, B, R );

    if( div < 0 ) { div = -div; a = -a; b = -b; c = -c; }

    return div;
  }

  return 0;
}


Int Math_NS::solve(
  const Vec& A,
  const Vec& B,
  const Vec& R,
  Int& a,
  Int& b )
{
  auto X = &Vec::x;
  auto Y = &Vec::y;
  auto Z = &Vec::z;

  auto det = [&]( const Vec& x, const Vec& y ){ return ( x.*X ) * ( y.*Y ) - ( x.*Y ) * ( y.*X ); };

  Int div = 0;

  //  find good pair of rows (XY) for solution lookup
  for( size_t i = 0; !( div = det( A, B ) ) && i < 3; ++i )
  {
    auto T = X;
    X = Y; Y = Z; Z = T;
  }

  if( div )
  {
    //  Solve in XY
    a = det( R, B );
    b = det( A, R );

    if( div < 0 ) { div = -div; a = -a; b = -b; }

    //  Check for Z
    if( a * A.*Z + b * B.*Z == div * R.*Z )
    {
      return div;
    }
  }

  return 0;
}


Int Math_NS::solve(
  const Vec& A,
  const Vec& R,
  Int& a )
{
  auto X = &Vec::x;
  auto Y = &Vec::y;
  auto Z = &Vec::z;

  Int div = 0;

  //  find good row (Z) for solution lookup
  for( size_t i = 0; !( div = A.*Z ) && i < 3; ++i )
  {
    auto T = X;
    X = Y; Y = Z; Z = T;
  }

  if( div )
  {
    //  Solve in Z
    a = R.*Z;

    if( div < 0 ) { div = -div; a = -a; }

    //  Check fo XY
    if( a * A.*X == div * R.*X && a * A.*Y == div * R.*Y )
    {
      return div;
    }
  }

  return 0;
}