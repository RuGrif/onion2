#pragma once


#include "Splice.h"
#include "../QEdge/Edge.h"
#include "../Collision/XPoint.h"


namespace Tailor_NS
{
  class XSplice
  {
  public:

    using XID = Collision_NS::XPointID;

    template <typename P0>
    XSplice( const P0& p0 ) : d_splice{ p0 } {}

    template <typename E, typename P1>
    void operator() ( QEdge_NS::Edge i_edge, E e, const P1& p1, const XID& xid1 )
    {
      d_splice( i_edge, p1.toXFace( e.e() ), xid1 );
    }

    QEdge_NS::Edge edge() const { return d_splice.edge(); }

  private:

    Splice d_splice;
  };
}