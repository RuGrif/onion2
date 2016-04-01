#pragma once


#include "../QEdge/Shape.h"
#include "../Collision/Intersection.h"
#include "Graph.h"
#include "Data.h"
#include <map>
#include "Tailor.h"


namespace Tailor_NS
{
  //  manage all intersection edges for one shape
  class Web
  {
  public:

    using XVertID = Collision_NS::XPointID;
    using XEdgeID = std::pair<XVertID, XVertID>;

    QEdge_NS::Edge getOrCreateEdge( const Collision_NS::XPointID& id0, const Collision_NS::XPointID& id1 );

    const QEdge_NS::Shape& web() const { return d_web; }

  private:

    std::map<XEdgeID, QEdge_NS::Edge>   d_edges;
    QEdge_NS::Shape                     d_web;
  };


  class TAILOR_API Spider
  {
  public:

    void spin( const Graph& g );

    const QEdge_NS::Shape& webA() const { return d_webA.web(); }
    const QEdge_NS::Shape& webB() const { return d_webB.web(); }

  private:

    Web d_webA;
    Web d_webB;
  };
}