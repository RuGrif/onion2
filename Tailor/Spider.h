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

    QEdge_NS::Edge getOrCreateEdge( const Collision_NS::XPointID& id0, const Collision_NS::XPointID& id1 )
    {
      auto f = d_edges.find( { id1, id0 } );  //  look for existing sym edge
      
      if( f != d_edges.end() )
      {
        return f->second.sym();
      }
      else
      {
        return d_edges[ { id0, id0 } ] = d_graph.makeEdge();
      }
    }

  private:

    std::map<XEdgeID, QEdge_NS::Edge>   d_edges;
    QEdge_NS::Shape                     d_graph;
  };


  class Spider
  {
  public:

    void spin( const Graph& g );

  private:

    Web webA, webB;
  };
}