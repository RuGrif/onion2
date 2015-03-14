#pragma once


#include "Primitive.h"
#include "Grid.h"
#include "Graph.h"
#include "Collision.h"


namespace Collision_NS
{
  class COLLISION_API Collider
  {
  public:

    using Int = Grid::Int;

    bool operator() ( Vert a, Vert b ) { return collide( a, b, false ); }
    bool operator() ( Vert a, Edge b ) { return collide( a, b, false ); }
    bool operator() ( Vert a, Face b ) { return collide( a, b, false ); }
    bool operator() ( Edge a, Vert b ) { return collide( b, a, true ); }
    bool operator() ( Edge a, Edge b ) { return collide( a, b, false ); }
    bool operator() ( Edge a, Face b ) { return collide( a, b, false ); }
    bool operator() ( Face a, Vert b ) { return collide( b, a, true ); }
    bool operator() ( Face a, Edge b ) { return collide( b, a, true ); }
    //  no need in face x face intersection

  private:

    bool collide( Vert, Vert, bool alter );
    bool collide( Vert, Edge, bool alter );
    bool collide( Vert, Face, bool alter );
    bool collide( Edge, Edge, bool alter );
    bool collide( Edge, Face, bool alter );

  private:

    Grid  grid;
    Graph graph;
  };
}