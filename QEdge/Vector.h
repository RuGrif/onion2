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
    T x{}, y{}, z{};

    Vector3() = default;
    Vector3( T x, T y, T z ) : x( x ), y( y ), z( z ) {}
  };


  using Vector2D = Vector2<double>;
  using Vector3D = Vector3<double>;

  using Vector2I = Vector2<long long int>;
  using Vector3I = Vector3<long long int>;


  template <typename T> bool operator == ( const Vector3<T>& a, const Vector3<T> &b ) { return a.x == b.x && a.y == b.y && a.z == b.z; }
}