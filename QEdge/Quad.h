#pragma once


#include "Loop.h"
#include "Node.h"


namespace QEdge_NS
{
  class Quad
  {
  public:

    using Prim = Loop<Vert>;
    using Dual = Loop<Face>;

    struct Edge {};
    struct Loop {};

    Quad( Edge ) : Quad() { l.fuse0( r ); }
    Quad( Loop ) : Quad() { o.fuse0( d ); }

    const Prim& edge() const { return o; }
    Prim&       edge()       { return o; }

  private:

    Prim o, d;
    Dual l, r;

  private:

    Quad() : o( r ), d( l ), l( o ), r( d ) {}

    Quad( const Quad& ) = delete;
    Quad& operator = ( const Quad& ) = delete;
  };
}