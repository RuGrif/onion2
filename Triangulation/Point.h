#pragma once


#include "../Math/IntType.h"


namespace Triangulation_NS
{
  template <typename T>
  struct PointType
  {
    T x, y;
    T d;
  };


  using Point = PointType<Math_NS::IntType>;


  template <typename T>
  auto makePoint( const T& x, const T& y, const T& d ) { return PointType<T>{ x, y, d }; }
}