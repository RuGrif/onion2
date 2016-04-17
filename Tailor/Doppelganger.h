#pragma once


#include <map>
#include "../Math/Rational.h"
#include "../Collision/XPoint.h"
#include "../QEdge/Shape.h"


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

    //  add intersection point on twin edge
    void insert( const Int& u, const Int& v, const Math_NS::Vector3D& p, const Collision_NS::XPointID& );

    //  replace real edge with a sequence of new edge
    void forgery( QEdge_NS::Shape&, QEdge_NS::Edge ) const;

  private:

    using Position = std::pair<Math_NS::RationalType, Collision_NS::XPointID>;

    std::map<Position, Math_NS::Vector3D> d_twin;
  };


  class TwinEdgeCollection
  {
  public:

    void insert( const Collision_NS::XVert&, const Math_NS::Vector3D&, const Collision_NS::XPointID& ) {}  //  empty
    void insert( const Collision_NS::XEdge&, const Math_NS::Vector3D&, const Collision_NS::XPointID& );
    void insert( const Collision_NS::XFace&, const Math_NS::Vector3D&, const Collision_NS::XPointID& ) {}  //  empty

    //  cut real edges
    void forgery( QEdge_NS::Shape& ) const;

  private:

    std::map<Collision_NS::Edge, TwinEdge> d_collection;
  };


  class Doppelganger
  {
  public:

    //  callback for Graph::forEachXPoint
    template <typename A, typename B>
    void operator() ( const Collision_NS::XPoint<A, B>& v )
    {
      const Math_NS::Vector3D p = point( v );
      d_doppelA.insert( v.first, p, Collision_NS::makeXPointID( v.first, v.second ) );
      d_doppelB.insert( v.second, p, Collision_NS::makeXPointID( v.second, v.first ) );
    }

    //  cut real edges
    void forgery( QEdge_NS::Shape& io_shapeA, QEdge_NS::Shape& io_shapeB ) const
    {
      d_doppelA.forgery( io_shapeA );
      d_doppelB.forgery( io_shapeB );
    }

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