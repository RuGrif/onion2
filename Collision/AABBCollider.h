#pragma once


#include "AABB.h"
#include <functional>


namespace Collision_NS
{
  class AABBCollider
  {
  public:

    using Box = Math_NS::Box3L;
    using Vec = Box::Vector3;

    using Callback = std::function<bool( Face, Face )>;

    AABBCollider( const Callback& i_callback ) : d_callback{ i_callback } {}

    bool collide( const AABBTree& a, const AABBTree& b ) { return collide( a.top(), b.top() ); }

  private:

    bool collide( const AABB&, const AABB& );

    static bool collide( const Box&, const Box& );

  private:

    Callback d_callback;
  };
}