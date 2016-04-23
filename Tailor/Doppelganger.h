#pragma once


#include "../Math/Rational.h"
#include "../Collision/XPoint.h"
#include "../QEdge/Shape.h"
#include <map>


//  Doppelganger is a mechanism to cut edge by intersection vertexes into sequence of new edges


namespace Tailor_NS
{
  class DuplicatedIntersectionPoint;


  class TwinStar : public QEdge_NS::VertData
  {
  public:

    TwinStar( const Math_NS::Vector3D& i_point ) : d_point{ i_point } {}

    virtual const Math_NS::Vector3D point() const override { return d_point; }

  private:

    Math_NS::Vector3D d_point;
  };


  class TwinEdge
  {
  public:

    using Int = Math_NS::Vector3L::Type;
    using XID = Collision_NS::XPointID;
    using Map = std::map<XID, QEdge_NS::Edge>;

    //  add intersection point on twin edge
    void insert( const Int& u, const Int& v, const Math_NS::Vector3D& p, const XID& );

    //  prepare a sequence of new edges to replace real edge
    void makeTwins( QEdge_NS::Shape& );

    QEdge_NS::Edge prev( const XID& ) const;
    QEdge_NS::Edge next( const XID& ) const;

    //  replace edge with a sequence of twin edges
    void substitute( QEdge_NS::Edge ) const;

  private:

    using Position = std::pair<Math_NS::RationalType, Collision_NS::XPointID>;

    std::map<Position, Math_NS::Vector3D>                     d_verts;
    std::map<XID, std::pair<QEdge_NS::Edge, QEdge_NS::Edge>>  d_edges;
  };


  class TwinEdgeCollection
  {
  public:

    void insert( const Collision_NS::XVert&, const Math_NS::Vector3D&, const Collision_NS::XPointID& ) {}  //  empty
    void insert( const Collision_NS::XEdge&, const Math_NS::Vector3D&, const Collision_NS::XPointID& );
    void insert( const Collision_NS::XFace&, const Math_NS::Vector3D&, const Collision_NS::XPointID& ) {}  //  empty

    //  prepare a sequence of new edges to replace real edge
    void makeTwins( QEdge_NS::Shape& );

    QEdge_NS::Edge prev( const Collision_NS::XPointID& ) const;
    QEdge_NS::Edge next( const Collision_NS::XPointID& ) const;

    //  replace edge with a sequence of twin edges
    void substitute() const;

  private:

    std::map<size_t, std::pair<Collision_NS::Edge, TwinEdge>> d_collection;
  };


  class Doppelganger
  {
  public:

    //  callback for TopoGraph::forEachXPoint
    template <typename A, typename B>
    void operator() ( const Collision_NS::XPoint<A, B>& v )
    {
      const Math_NS::Vector3D p = point( v );
      d_doppelA.insert( v.first, p, Collision_NS::makeXPointID( v.first, v.second ) );
      d_doppelB.insert( v.second, p, Collision_NS::makeXPointID( v.second, v.first ) );
    }

    //  prepare a sequence of new edges to replace real edge
    void makeTwins( QEdge_NS::Shape&, QEdge_NS::Shape& );

    const TwinEdgeCollection& getDoppelgangerA() const { return d_doppelA; }
    const TwinEdgeCollection& getDoppelgangerB() const { return d_doppelB; }

    //  replace edge with a sequence of twin edges
    void substitute() const;

  private:

    TwinEdgeCollection d_doppelA;
    TwinEdgeCollection d_doppelB;
  };


  class DuplicatedIntersectionPoint : public std::exception
  {
  public:

    DuplicatedIntersectionPoint( const Collision_NS::XPointID& i_xid ) : d_xid{ i_xid } {}

    virtual const char*             what()  const override  { return "duplicated intersection vertex on edge"; }
    const Collision_NS::XPointID&   xid()   const           { return d_xid; }

  private:

    const Collision_NS::XPointID d_xid;
  };
}