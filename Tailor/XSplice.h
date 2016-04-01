#pragma once


#include "../QEdge/Edge.h"
#include "../Collision/Intersection.h"


namespace Tailor_NS
{
  template <typename P0>
  class XSplice
  {
  public:

    XSplice( const P0& p0 ) : p0{ p0 } {}

    template <typename P1>
    void operator() ( QEdge_NS::Edge e, const P1& p1 )
    {
      if( o ) e.splice0( o );
      o = e;
    }

  private:

    const P0&       p0;
    QEdge_NS::Edge  o;
  };
}