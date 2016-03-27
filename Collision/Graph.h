#pragma once


#include "Intersection.h"
#include <memory>
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

    void operator()( std::unique_ptr<Intersection>&& );

    using Nodes = std::vector<std::reference_wrapper<const Intersection>>;

    Nodes all() const;
    Nodes neighborhood( const Intersection& ) const;

  private:

    #pragma warning( suppress : 4251 )
    std::unordered_map<Intersection::ID, std::unique_ptr<Intersection>> d_verts;
  };
}