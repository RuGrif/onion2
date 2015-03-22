#include "AABBCollider.h"


bool Collision_NS::AABBCollider::collideAll( const AABB& a, const AABB& b )
{
  if( ( a.box() * b.box() ).empty() ) return false;

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