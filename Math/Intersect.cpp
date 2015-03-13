#include "Intersect.h"
#include <utility>


namespace Math_NS
{
  //  shortcuts
  using Vec = IS_NS::Vec;
  using Int = IS_NS::Int;

  //  determinant of matrix || a  b  c ||
  Int det( const Vec& a, const Vec& b, const Vec& c ) { return ( a ^ b ) * c; }
  
  //  2D version of determinant on XY plane
  Int det( const Vec& a, const Vec& b ) { return a.x * b.y - a.y * b.x; }
}


void Math_NS::intersect(
  const Vec& A, const Vec& B, const Vec& C,
  const Vec& U, const Vec& V,
  FaceEdge& i_callback )
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

  Vec ea = A - C;
  Vec eb = B - C;
  Vec eu = V - U;

  if( Int div = det( ea, eb, eu ) )
  {
    //
    //  Normal scenario
    //

    Vec rhs = V - C;
    
    Int a = det( rhs, eb, eu );
    Int b = det( ea, rhs, eu );
    Int u = det( ea, eb, rhs );

    if( div < 0 )
    {
      div = -div;
      a = -a;
      b = -b;
      u = -u;
    }

    if( a >= 0 && b >= 0 && a <= div - b && u >= 0 && u <= div )
    {
      i_callback( a, b, div - a - b, u, div - u, div );
    }
  }
  else
  {
    //
    //  Degenerated scenario level 1: edge parallel to the face plane
    //

    intersect( A, B, U, V, i_callback.AB() );
    intersect( B, C, U, V, i_callback.BC() );
    intersect( C, A, U, V, i_callback.CA() );
  }
}


void Math_NS::intersect(
  const Vec& A, const Vec& B,
  const Vec& U, const Vec& V,
  EdgeEdge& i_callback )
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

  Vec ea = A - B;
  Vec eu = V - U;
  Vec rhs = V - B;

  Vec n = ea ^ eu;

  //  make n.z != 0
  if( !n.z )
  {
    if( !n.y )
    {
      //  X -> Z
      std::swap( ea.x, ea.z );
      std::swap( eu.x, eu.z );
      std::swap( rhs.x, rhs.z );
      std::swap( n.x, n.z );
    }
    else
    {
      //  Y -> Z
      std::swap( ea.y, ea.z );
      std::swap( eu.y, eu.z );
      std::swap( rhs.y, rhs.z );
      std::swap( n.y, n.z );
    }
  }
  
  if( Int div = n.z )
  {
    //
    //  Normal scenario
    //

    Int a = det( rhs, eu );
    Int u = det( ea, rhs );

    if( div < 0 )
    {
      div = -div;
      a = -a;
      u = -u;
    }

    //  check solution for Z
    if( a * ea.z + u * eu.z == div * rhs.z 
      && a >= 0 && a <= div && u >= 0 && u <= div )
    {
      i_callback( a, div - a, u, div - u, div );
    }
  }
  else
  {
    //
    //  Degenerated scenario level 2: edges are parallel
    //

    intersect( A, U, V, i_callback.A() );
    intersect( B, U, V, i_callback.B() );
  }
}


void Math_NS::intersect(
  const Vec& A,
  const Vec& U, const Vec& V,
  VertEdge& i_callback )
{
  //  A = u * U + v * V
  //  u + v = 1
  //
  //  v = 1 - u
  //  A = u * ( U - V ) + V
  //  u * ( V - U ) = V - A

  Vec e = V - U;
  Vec rhs = V - A;

  //  make e.z != 0
  if( !e.z )
  {
    if( !e.y )
    {
      //  X -> Z
      std::swap( e.x, e.z );
      std::swap( rhs.x, rhs.z );
    }
    else
    {
      //  Y -> Z
      std::swap( e.y, e.z );
      std::swap( rhs.y, rhs.z );
    }
  }
  
  if( Int div = e.z )
  {
    Int u = rhs.z;

    if( div < 0 )
    {
      div = -div;
      u = -u;
    }
    
    if( u * e.x == rhs.x && u * e.y == rhs.y && u >= 0 && u <= e.x )
    {
      i_callback( u, div - u, div );
    }
  }
}