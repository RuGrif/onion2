#pragma once


#include "Point.h"
#include "../QEdge/Data.h"


namespace Triangulation_NS
{
  //  check if point p is to the left-hand side from line { a, b }
  bool isAtLeftSide( const Point& a, const Point& b, const Point& p );

  //  check if point p is inside the triangle { a, b, c }
  bool isInsideTriangle( const Point& a, const Point& b, const Point& c, const Point& p );
}