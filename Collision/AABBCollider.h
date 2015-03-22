#pragma once


#include "Collider.h"
#include "AABB.h"
#include "Collision.h"


namespace Collision_NS
{
  class COLLISION_API AABBCollider
  {
  public:

    bool collideFirst( const AABB&, const AABB& );
    bool collideAll( const AABB&, const AABB& );

    const Collider& collider() const { return d_collider; }

  private:

    Collider d_collider;
  };
}