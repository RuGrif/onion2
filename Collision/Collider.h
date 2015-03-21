#pragma once


#include "Primitive.h"
#include "..\Math\Grid.h"
#include "Graph.h"
#include "Collision.h"


namespace Collision_NS
{
  class COLLISION_API Collider
  {
  public:

    using Vec = Math_NS::Vector3L;
    using Int = Vec::Type;

    bool operator() ( Vert a, Vert b ) { return collide( a, b, false ); }
    bool operator() ( Vert a, Edge b ) { return collide( a, b, false ); }
    bool operator() ( Vert a, Face b ) { return collide( a, b, false ); }
    bool operator() ( Edge a, Vert b ) { return collide( b, a, true ); }
    bool operator() ( Edge a, Edge b ) { return collide( a, b, false ); }
    bool operator() ( Edge a, Face b ) { return collide( a, b, false ); }
    bool operator() ( Face a, Vert b ) { return collide( b, a, true ); }
    bool operator() ( Face a, Edge b ) { return collide( b, a, true ); }
    bool operator() ( Face a, Face b );

    const Graph& graph() const { return d_graph; }

  private:

    bool collide( Vert, Vert, bool alter );
    bool collide( Vert, Edge, bool alter );
    bool collide( Vert, Face, bool alter );
    bool collide( Edge, Edge, bool alter );
    bool collide( Edge, Face, bool alter );

    Math_NS::Vector3L grid( const Math_NS::Vector3D& p ) const { return d_grid( p ); }

  private:

    Math_NS::Grid   d_grid;
    Graph           d_graph;
  };
}