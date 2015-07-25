#include "Hash.h"
#include <cinttypes>


template <> struct std::hash<Math_NS::Vector3F>
{
  std::size_t operator() ( const Math_NS::Vector3F& p ) const
  {
    auto hash = std::hash<float>();

    const size_t s = 8 * sizeof( size_t ) / 3;

    return hash( p.x )
      ^ ( hash( p.y ) << s )
      ^ ( hash( p.z ) << 2 * s );
  }
};


template <> struct std::hash<std::pair<Math_NS::Vector3F, Math_NS::Vector3F>>
{
  std::size_t operator() ( const std::pair<Math_NS::Vector3F, Math_NS::Vector3F>& p ) const
  {
    auto hash = std::hash<float>();

    const size_t s = 8 * sizeof( size_t ) / 6;

    return hash( p.first.x )
      ^ ( hash( p.first.y ) << 2 * s )
      ^ ( hash( p.first.z ) << 4 * s )
      ^ ( hash( p.second.x ) << s )
      ^ ( hash( p.second.x ) << 3 * s )
      ^ ( hash( p.second.x ) << 5 * s );
  }
};