#pragma once


#include "TopoGraph.h"
#include "../Math/Rational.h"
#include "../Collision/XPoint.h"
#include "../QEdge/Shape.h"
#include <map>
#include <set>


//  Doppelganger is a mechanism to cut edge by intersection vertexes into sequence of new edges


namespace Tailor_NS
{
  class TwinEdge
  {
  public:

    using Int = Math_NS::Vector3L::Type;
    using XID = Collision_NS::XPointID;
    using Map = std::map<XID, QEdge_NS::Edge>;

    using Position = std::pair<Math_NS::RationalType, XID>;
    using EdgePair = std::pair<QEdge_NS::Edge, QEdge_NS::Edge>;

    //  add intersection point on twin edge
    void insert( const Int& u, const Int& v, const XID& );

    //  prepare a sequence of new edges to replace real edge
    void makeTwins( QEdge_NS::Shape& );

    //  a pair of previous and next edges for given intersection point
    //  geometrically both edges have origin in intersection point
    //  topologically both edges are not connected
    EdgePair edgePair( const XID& ) const;

    //  replace edge with a sequence of twin edges
    void substitute( QEdge_NS::Edge ) const;

  public:

    const auto& collection() const { return d_edges; } //  for unit tests

  private:

    std::set<Position>        d_verts;
    std::map<XID, EdgePair>   d_edges;
  };


  class TwinEdgeCollection
  {
  public:

    void insert( const Collision_NS::XVert&, const Collision_NS::XPointID& ) {}  //  empty
    void insert( const Collision_NS::XEdge&, const Collision_NS::XPointID& );
    void insert( const Collision_NS::XFace&, const Collision_NS::XPointID& ) {}  //  empty

    //  prepare a sequence of new edges to replace real edge
    void makeTwins( QEdge_NS::Shape& );

    using EdgePair = std::pair<QEdge_NS::Edge, QEdge_NS::Edge>;

    //  get twin for given edge id
    const TwinEdge& twinEdge( size_t ) const;

    //  replace edge with a sequence of twin edges
    void substitute() const;

  public:

    const auto& collection() const { return d_collection; } //  for unit tests

  private:

    std::map<size_t, std::pair<Collision_NS::Edge, TwinEdge>> d_collection;
  };


  class Doppelganger
  {
  public:

    //  add intersection points on edges
    void shadow( const TopoGraph& g );

    //  prepare a sequence of new edges to replace real edge
    void makeTwins( QEdge_NS::Shape&, QEdge_NS::Shape& );

    const TwinEdgeCollection& getDoppelgangerA() const { return d_doppelA; }
    const TwinEdgeCollection& getDoppelgangerB() const { return d_doppelB; }

    //  replace edge with a sequence of twin edges
    void substitute() const;

    //  callback for TopoGraph::forEachXPoint
    template <typename A, typename B>
    void operator() ( const Collision_NS::XPoint<A, B>& );

  private:

    TwinEdgeCollection d_doppelA;
    TwinEdgeCollection d_doppelB;
  };
}