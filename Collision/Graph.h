#pragma once


#include "Primitive.h"
#include <memory>
#include <unordered_set>


namespace Collision_NS
{
  //  Intersection vertex
  using Node = std::pair<std::unique_ptr<Prim>, std::unique_ptr<Prim>>;
  bool operator == ( const Node&, const Node& );
}


template <> struct std::hash<Collision_NS::Node>
{
  using N = Collision_NS::Node;
  std::size_t operator() ( const N& n ) const;
};


namespace Collision_NS
{
  //  Intersection map
  class Graph
  {
    std::unordered_set<Node> d_verts;

  public:

    using Neighborhood = std::list<Node>;

    Neighborhood neighborhood( const Node& ) const;
  };
}