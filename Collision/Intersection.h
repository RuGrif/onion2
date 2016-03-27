#pragma once


#include "Primitive.h"


namespace Collision_NS
{
  //  Intersection vertex
  struct Intersection
  {
    using ID                    = std::pair<size_t, size_t>;

    virtual Prim&                 alpha() const = 0;
    virtual Prim&                 beta() const = 0;

    virtual Math_NS::Vector3D     intersection() const = 0;

    ID                            id() const { return{ alpha(), beta() }; }

    virtual                       ~Intersection() {}
  };
}


template <> struct std::hash<Collision_NS::Intersection::ID>
{
  std::size_t operator() ( const Collision_NS::Intersection::ID& id ) const { return id.first ^ id.second; }
};
