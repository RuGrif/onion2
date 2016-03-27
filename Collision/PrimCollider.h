#pragma once


#include "Primitive.h"
#include "Intersection.h"
#include "..\Math\Grid.h"
#include <functional>
#include "Collision.h"


namespace Collision_NS
{
  class COLLISION_API PrimCollider
  {
  public:

    using Vec = Math_NS::Vector3L;
    using Int = Vec::Type;

    using Callback = std::function<void( std::unique_ptr<Intersection>&& )>;

    PrimCollider( const Callback& i_callback, const Math_NS::Grid& i_grid ) : d_callback{ i_callback }, d_grid{ i_grid } {}

    bool operator() ( Vert a, Vert b ) { return collide( a, b, false ); }
    bool operator() ( Vert a, Edge b ) { return collide( a, b, false ); }
    bool operator() ( Vert a, Face b ) { return collide( a, b, false ); }
    bool operator() ( Edge a, Vert b ) { return collide( b, a, true ); }
    bool operator() ( Edge a, Edge b ) { return collide( a, b, false ); }
    bool operator() ( Edge a, Face b ) { return collide( a, b, false ); }
    bool operator() ( Face a, Vert b ) { return collide( b, a, true ); }
    bool operator() ( Face a, Edge b ) { return collide( b, a, true ); }
    bool operator() ( Face a, Face b );

  private:

    bool collide( Vert, Vert, bool alter );
    bool collide( Vert, Edge, bool alter );
    bool collide( Vert, Face, bool alter );
    bool collide( Edge, Edge, bool alter );
    bool collide( Edge, Face, bool alter );

    Math_NS::Vector3L grid( const Math_NS::Vector3D& p ) const { return d_grid( p ); }

  private:

    #pragma warning( suppress : 4251 )
    Callback        d_callback;
    Math_NS::Grid   d_grid;
  };
}