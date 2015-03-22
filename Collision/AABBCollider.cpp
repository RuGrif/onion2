#include "AABBCollider.h"
#include <utility>


bool Collision_NS::AABBCollider::collideAll( const AABB& a, const AABB& b )
{
  if( !collide( a.box(), b.box() ) ) return false;

  if( a.isFace() )
  {
    if( b.isFace() )
    {
      return d_collider( a.face(), b.face() );
    }
    else
    {
      bool r = false;

      r |= collideAll( a, b.left() );
      r |= collideAll( a, b.right() );

      return r;
    }
  }
  else
  {
    if( b.isFace() )
    {
      bool r = false;

      r |= collideAll( a.left(), b );
      r |= collideAll( a.left(), b );

      return r;
    }
    else
    {
      bool r = false;

      r |= collideAll( a.left(), b.left() );
      r |= collideAll( a.left(), b.right() );
      r |= collideAll( a.right(), b.left() );
      r |= collideAll( a.right(), b.right() );

      return r;
    }
  }
}


bool Collision_NS::AABBCollider::collide( const Box& a, const Box& b )
{
  return
    std::max( a.min.x, b.min.x ) <= std::min( a.max.x, b.max.x ) &&
    std::max( a.min.y, b.min.y ) <= std::min( a.max.y, b.max.y ) &&
    std::max( a.min.z, b.min.z ) <= std::min( a.max.z, b.max.z );
}