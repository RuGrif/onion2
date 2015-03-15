#pragma once


#include "Primitive.h"


namespace Collision_NS
{
  using NodeId = std::pair<size_t, size_t>;

  //  Intersection vertex
  struct Node
  {
    virtual Prim&                 alpha() const = 0;
    virtual Prim&                 beta() const = 0;

    virtual Math_NS::Vector3D     intersection() const = 0;

    NodeId                        id() const { return{ alpha(), beta() }; }

    virtual                       ~Node() {}
  };
}


template <> struct std::hash<Collision_NS::NodeId>
{
  std::size_t operator() ( const Collision_NS::NodeId& id ) const { return id.first ^ id.second; }
};
