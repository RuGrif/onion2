#pragma once


#include "Vector3.h"
#include "Math.h"


namespace Math_NS
{
  class Point
  {
  public:

    using Vec = Vector3L;
    using Int = Vec::Type;

    Point( const Vec& i_point ) : d_point( i_point ) {}

    //  access vertex coordinates
    const Vec& point() const { return d_point; }
    
    //  access barycentric coordinate of intersection
    Int weight() const { return d_weight; }
    void weight( Int i_weight ) { d_weight = i_weight; }

    //  return weighted vertex coordinates
    Vec operator * ( ) const { return weight() * point();  }

  private:

    Vec d_point{};
    Int d_weight{};
  };

  //  collides triangle ABC with edge UV
  //  return zero in gegenerated case; otherwise return divisor
  MATH_API Point::Int intersect(
    Point& A, Point& B, Point& C,
    Point& U, Point& V );

  //  collides edge AB with edge UV
  //  return zero in gegenerated case; otherwise return divisor
  MATH_API Point::Int intersect(
    Point& A, Point& B,
    Point& U, Point& V );

  //  collides vert A with edge UV
  //  return zero in gegenerated case; otherwise return divisor
  MATH_API Point::Int intersect(
    Point& A,
    Point& U, Point& V );
}