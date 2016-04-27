#include "InsideTest.h"
#include "../Math/Rational.h"


bool Triangulation_NS::isAtLeftSide(
  const Point& a,
  const Point& b,
  const Point& p )
{
  //  line given by next equation
  //  ( x - a.x ) / ( b.x - a.x ) == ( y - a.y ) / ( b.y - a.y )
  //  same as
  //  ( a - a.x ) * ( b.y - a.y ) - ( y - a.y ) * ( b.x - a.x ) == 0
  //  now, normal to line is
  //  n = { ( a.y - b.y ), ( b.x - a.x ) }

  using Math_NS::makeRational;
  using Math_NS::prod;
  
  //  l = ( b - a )
  auto lx = prod( b.x, a.d ) - prod( a.x, b.d );
  auto ly = prod( b.y, a.d ) - prod( a.y, b.d );

  //  r = ( p - a )
  auto rx = prod( p.x, a.d ) - prod( a.x, p.d );
  auto ry = prod( p.y, a.d ) - prod( a.y, p.d );

  //  n = { -l.y, l.x }
  //  r * n = { r.x, r.y } * { -l.y, l.x } = r.y * l.x - r.x * l.y > 0
  //  r.x * l.y < r.y * l.x
  return prod( rx, ly ) < prod( ry, lx );
}


bool Triangulation_NS::isInsideTriangle( const Point& a, const Point& b, const Point& c, const Point& p )
{
  return isAtLeftSide( a, b, p ) && isAtLeftSide( b, c, p ) && isAtLeftSide( c, a, p );
}
