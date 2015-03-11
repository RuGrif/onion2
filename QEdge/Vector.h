#pragma once


namespace QEdge_NS
{
  template <typename T>
  struct Vector2
  {
    T x, y;
  };


  template <typename T>
  struct Vector3
  {
    T x, y, z;
  };


  using Vector2D = Vector2<double>;
  using Vector3D = Vector3<double>;

  using Vector2I = Vector2<long long int>;
  using Vector3I = Vector3<long long int>;
}