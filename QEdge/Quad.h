#pragma once


#include "Loop.h"
#include "Node.h"


namespace QEdge_NS
{
  class Quad
  {
  public:

    using Prim = Loop<VertTraits>;
    using Dual = Loop<FaceTraits>;

    struct Edge {};
    struct Loop {};

    Quad( Edge ) : Quad() { l.fuse0( r ); }
    Quad( Loop ) : Quad() { o.fuse0( d ); }

    const Prim& edge() const { return o; }
    Prim&       edge()       { return o; }

    bool isIsolatedEdge() const { return &o.next() == &o && &d.next() == &d; }
    bool isIsolatedLoop() const { return &l.next() == &l && &r.next() == &r; }

  private:

    Prim o, d;
    Dual l, r;

  private:

    Quad() : o( r ), d( l ), l( o ), r( d ) {} //-V670

    Quad( const Quad& ) = delete;
    Quad& operator = ( const Quad& ) = delete;
  };
}