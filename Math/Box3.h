#pragma once


#include "Vector3.h"
#include <limits>


namespace Math_NS
{
  template <typename T>
  struct Box3
  {
    using Vector3 = Vector3<T>;
    using Type = T;

    Vector3 min{ std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max() };
    Vector3 max{ std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest() };

    Box3() = default;
    Box3( const Vector3& v ) : min( v ), max( v ) {}
    Box3( const Vector3& min, const Vector3& max ) : min( min ), max( max ) {}

    bool  empty() const { return max.x < min.x || max.y < min.y || max.z < min.z; }
    T     volume() const { return ( max.x - min.x ) * ( max.y - min.y ) * ( max.z - min.z ); }

    Box3& operator += ( const Vector3& v ) { min = Math_NS::min( min, v ); max = Math_NS::max( max, v ); return *this; }
    Box3& operator += ( const Box3& box ) { min = Math_NS::min( min, box.min ); max = Math_NS::max( max, box.max ); return *this; }

    Box3& operator *= ( const Box3& box ) { min = Math_NS::max( min, box.min ); max = Math_NS::min( max, box.max ); return *this; }
  };


  template <typename T> Box3<T> operator + ( const Box3<T>& a, const Box3<T>& b ) { return Box3<T>( a ) += b; }
  template <typename T> Box3<T> operator + ( const Box3<T>& b, const Vector3<T>& v ) { return Box3<T>( b ) += v; }
  template <typename T> Box3<T> operator + ( const Vector3<T>& v, const Box3<T>& b ) { return Box3<T>( b ) += v; }

  template <typename T> Box3<T> operator * ( const Box3<T>& a, const Box3<T>& b ) { return Box3<T>( a ) *= b; }


  using Box3D = Box3<double>;
  using Box3F = Box3<float>;
  using Box3I = Box3<int>;
  using Box3L = Box3<Vector3L::Type>;
}