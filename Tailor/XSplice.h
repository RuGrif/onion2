#pragma once


#include "../QEdge/Edge.h"
#include "../Collision/XPoint.h"
#include <array>
#include <map>


namespace Tailor_NS
{
  //class XCache
  //{
  //  using XFace = Collision_NS::XFace;
  //  using Edge = QEdge_NS::Edge;

  //  std::array<std::pair<XFace, Edge>, 2> d_cache;
  //  std::map<XFace, Edge>;
  //};


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

    QEdge_NS::Edge edge() const { return o; }

  private:

    const P0&       p0;
    QEdge_NS::Edge  o;
  };
}