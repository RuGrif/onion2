#pragma once


#include "Node.h"
#include <unordered_map>
#include <vector>
#include <functional>
#include "Collision.h"


namespace Collision_NS
{
  //  Intersection map
  class COLLISION_API Graph
  {
    Graph( const Graph& ) = delete;
    Graph& operator = ( const Graph& ) = delete;

  public:

    Graph() = default;

    void push( Node&& );

    using Neighborhood = std::vector<std::reference_wrapper<const Node>>;

    Neighborhood neighborhood( const Node& ) const;

  private:

    #pragma warning( suppress : 4251 )
    std::unordered_map<NodeId, Node> d_verts;
  };
}