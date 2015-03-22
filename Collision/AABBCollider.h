#pragma once


#include "Collider.h"
#include "AABB.h"
#include "Collision.h"


namespace Collision_NS
{
  class COLLISION_API AABBCollider
  {
  public:

    using Box = Math_NS::Box3L;
    using Vec = Box::Vector3;

    bool collideFirst( const AABB&, const AABB& );
    bool collideAll( const AABB&, const AABB& );

    static bool collide( const Box&, const Box& );

    const Collider& collider() const { return d_collider; }

  private:

    Collider d_collider;
  };
}