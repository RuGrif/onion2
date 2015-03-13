#include "Intersect.h"


namespace Math_NS
{
  //  shortcuts
  using Vec = Point::Vec;
  using Int = Point::Int;

  //  3D determinant of matrix || a  b  c ||
  Int det( const Vec& ea, const Vec& eb, const Vec& ec ) { return ( ea ^ eb ) * ec; }
  
  //  2D determinant of matrix || xx  xy ||
  //                           || yx  yy ||
  Int det( Int xx, Int xy, Int yx, Int yy) { return xx * yy - xy * yx; }
}


Math_NS::Point::Int Math_NS::intersect(
  Point& A, Point& B, Point& C,
  Point& U, Point& V )
{
  //  a * A + b * B + c * C = u * U + v * V
  //  a + b + c = 1
  //  u + v = 1
  //
  //  c = 1 - a - b
  //  v = 1 - u
  //
  //  a * ( A - C ) + b * ( B - C ) + C = u * ( U - V ) + V
  //  a * ( A - C ) + b * ( B - C ) + u * ( V - U ) = V - C

  Vec ea = A.point() - C.point();
  Vec eb = B.point() - C.point();
  Vec eu = V.point() - U.point();

  if( Int div = det( ea, eb, eu ) )
  {
    Vec rh = V.point() - C.point();

    Int a = det( rh, eb, eu );
    Int b = det( ea, rh, eu );
    Int u = det( ea, eb, rh );
    
    A.weight( a );
    B.weight( b );
    C.weight( div - a - b );
    U.weight( u );
    V.weight( div - u );

    return div;
  }

  return 0;
}


Math_NS::Point::Int Math_NS::intersect(
  Point& A, Point& B,
  Point& U, Point& V )
{
  //  a * A + b * B = u * U + v * V
  //  a + b = 1
  //  u + v = 1
  //
  //  b = 1 - a
  //  v = 1 - u
  //
  //  a * ( A - B ) + B = u * ( U - V ) + V
  //  a * ( A - B ) + u * ( V - U ) = V - B

  Vec ea = A.point() - B.point();
  Vec eu = V.point() - U.point();
  Vec rh = V.point() - B.point();

  Int Vec::*X = &Vec::x;
  Int Vec::*Y = &Vec::y;
  Int Vec::*Z = &Vec::z;

  auto xdet = [&]( const Vec& ea, const Vec& eb ){ return det( ea.*X, ea.*Y, eb.*X, eb.*Y ); };

  Int div = 0;

  //  find good pair of rows (XY) for solution lookup
  for( size_t i = 0; !( div = xdet( ea, eu ) ) && i < 3; ++i )
  {
    Int Vec::*T = X;
    X = Y; Y = Z; Z = T;
  }
  
  if( div )
  {
    //  Solve in XY
    Int a = xdet( rh, eu );
    Int u = xdet( ea, rh );

    //  Check for Z
    if( a * ea.*Z + u * eu.*Z == div * rh.*Z )
    {
      A.weight( a );
      B.weight( div - a );
      U.weight( u );
      V.weight( div - u );

      return div;
    }
  }
  
  return 0;
}


Math_NS::Point::Int Math_NS::intersect(
  Point& A,
  Point& U, Point& V )
{
  //  A = u * U + v * V
  //  u + v = 1
  //
  //  v = 1 - u
  //  A = u * ( U - V ) + V
  //  u * ( V - U ) = V - A

  Vec eu = V.point() - U.point();
  Vec rh = V.point() - A.point();

  Int Vec::*X = &Vec::x;
  Int Vec::*Y = &Vec::y;
  Int Vec::*Z = &Vec::z;

  Int div = 0;

  //  find good row (Z) for solution lookup
  for( size_t i = 0; !( div = eu.*Z ) && i < 3; ++i )
  {
    Int Vec::*T = X;
    X = Y; Y = Z; Z = T;
  }
  
  if( div )
  {
    //  Solve in Z
    Int u = rh.*Z;
    
    //  Check fo XY
    if( u * eu.*X == div * rh.*X && u * eu.*Y == div * rh.*Y )
    {
      A.weight( div );
      U.weight( u );
      V.weight( div - u );

      return div;
    }
  }
  
  return 0;
}