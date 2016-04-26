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
    void makeTwins();

    using EdgePair = std::pair<QEdge_NS::Edge, QEdge_NS::Edge>;

    //  get twin for given edge id
    const TwinEdge& twinEdge( size_t ) const;

    //  replace edge with a sequence of twin edges
    void substitute() const;

    const QEdge_NS::Shape& twin() const { return d_twin; }
    QEdge_NS::Shape&       twin()       { return d_twin; }

  public:

    const auto& collection() const { return d_collection; } //  for unit tests

  private:

    using Replica = std::pair<Collision_NS::Edge, TwinEdge>;
    
    std::map<size_t, Replica> d_collection;
    QEdge_NS::Shape           d_twin;
  };


  class Doppelganger
  {
  public:

    //  add intersection points on edges
    void shadow( const TopoGraph& g );

    //  prepare a sequence of new edges to replace real edge
    void makeTwins();

    const TwinEdgeCollection& getDoppelgangerA() const { return d_doppelA; }
    const TwinEdgeCollection& getDoppelgangerB() const { return d_doppelB; }

    //  replace edge with a sequence of twin edges
    void substitute() const;

    const QEdge_NS::Shape& twinA() const { return d_doppelA.twin(); }
    const QEdge_NS::Shape& twinB() const { return d_doppelB.twin(); }

    QEdge_NS::Shape& twinA() { return d_doppelA.twin(); }
    QEdge_NS::Shape& twinB() { return d_doppelB.twin(); }

    //  callback for TopoGraph::forEachXPoint
    template <typename A, typename B>
    void operator() ( const Collision_NS::XPoint<A, B>& );

  private:

    TwinEdgeCollection d_doppelA;
    TwinEdgeCollection d_doppelB;
  };
}