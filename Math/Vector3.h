#pragma once


namespace Math_NS
{
  template <typename T>
  struct Vector3
  {
    using type = T;

    T x{}, y{}, z{};

    Vector3() = default;
    Vector3( T x, T y, T z ) : x( x ), y( y ), z( z ) {}
  };


  template <typename T> bool operator == ( const Vector3<T>& a, const Vector3<T> &b ) { return a.x == b.x && a.y == b.y && a.z == b.z; }


  using Vector3D = Vector3<double>;
  using Vector3F = Vector3<float>;
  using Vector3I = Vector3<int>;
  using Vector3L = Vector3<long long int>;
}