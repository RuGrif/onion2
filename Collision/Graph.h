#pragma once


#include "Primitive.h"
#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>


namespace Collision_NS
{
  using NodeId = std::pair<size_t, size_t>;

  //  Intersection vertex
  class Node
  {
  public:

    template<typename A, typename B>
    Node( QEdge_NS::Edge, QEdge_NS::Edge );

    Prim& alpha() const { return *d_alpha; }
    Prim& beta() const { return *d_beta; }

  private:

    std::unique_ptr<Prim> d_alpha;
    std::unique_ptr<Prim> d_beta;
  };

  bool operator == ( const Node&, const Node& );
}


template <> struct std::hash<Collision_NS::NodeId>
{
  std::size_t operator() ( const Collision_NS::NodeId& ) const;
};


namespace Collision_NS
{
  //  Intersection map
  class Graph
  {
    std::unordered_map<NodeId, Node> d_verts;

  public:

    using Neighborhood = std::vector<std::reference_wrapper<const Node>>;

    Neighborhood neighborhood( const Node& ) const;
  };
}