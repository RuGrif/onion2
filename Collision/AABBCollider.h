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

    const Collider& collider() const { return d_collider; }

    bool collide( const AABBTree& a, const AABBTree& b ) { return collide( a.top(), b.top() ); }

  private:

    bool collide( const AABB&, const AABB& );

    static bool collide( const Box&, const Box& );

  private:

    Collider d_collider;
  };
}