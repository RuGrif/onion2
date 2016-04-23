#pragma once


#include "TopoGraph.h"
#include "Doppelganger.h"
#include "DeferSplice.h"
#include "../QEdge/Shape.h"
#include "../Collision/XPoint.h"
#include <map>


namespace Tailor_NS
{
  //  manage all intersection edges for one shape
  class Web
  {
  public:

    using XVertID = Collision_NS::XPointID;
    using XEdgeID = std::pair<XVertID, XVertID>;

    QEdge_NS::Edge getOrCreateEdge( const Collision_NS::XPointID&, const Collision_NS::XPointID& );

    const QEdge_NS::Shape& web() const { return d_web; }
    QEdge_NS::Shape&       web()       { return d_web; }

  private:

    std::map<XEdgeID, QEdge_NS::Edge>   d_edges;
    QEdge_NS::Shape                     d_web;
  };


  class Spider
  {
  public:

    DeferSplice spin( const TopoGraph&, const Doppelganger& );

    const QEdge_NS::Shape& webA() const { return d_webA.web(); }
    const QEdge_NS::Shape& webB() const { return d_webB.web(); }

    QEdge_NS::Shape& webA() { return d_webA.web(); }
    QEdge_NS::Shape& webB() { return d_webB.web(); }

  private:

    Web d_webA;
    Web d_webB;
  };
}