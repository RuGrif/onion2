#pragma once


//
//  intersection segment with defined operator <
//


#include "Angle.h"
#include "../Collision/Primitive.h"
#include "../Collision/XPoint.h"


namespace Tailor_NS
{
  struct BadOrbit : std::exception
  {
    virtual const char* what() const override { return "Bad orbit"; }

    BadOrbit( size_t fid, size_t oid ) : fid{ fid }, oid{ oid } {}

    const size_t fid;
    const size_t oid;
  };


  //  defines order number of face f around orbit o
  size_t orbit( Collision_NS::Face f, Collision_NS::Vert o ); //  count from edge with min id
  size_t orbit( Collision_NS::Face f, Collision_NS::Edge o ); //  major face < minor face
  size_t orbit( Collision_NS::Face f, Collision_NS::Face o );


  Collision_NS::Face toFace( Collision_NS::Vert );
  Collision_NS::Face toFace( Collision_NS::Edge );
  Collision_NS::Face toFace( Collision_NS::Face );


  class Ray
  {
  public:

    using SID = Collision_NS::XSegmentID;

    //  construct segment from intersection edge
    template <typename P0, typename E, typename P1>
    Ray( const P0&, E, const P1&, const Collision_NS::XSegmentID& );

    //  construct segment from real edge with intersection point on it
    Ray( Collision_NS::Edge );

    //  construct segment from real edge with intersection point in vertex in edge origin
    Ray( Collision_NS::Vert );

    friend bool operator < ( const Ray&, const Ray& );

    const SID& sid() const { return d_sid; }

  private:

    template <typename P0, typename P1>
    Ray( const P0&, const P1&, const Collision_NS::XSegmentID&, Collision_NS::Face );

  private:

    size_t    d_orbit;
    Angle     d_angle;
    SID       d_sid;
  };


  bool operator < ( const Ray& l, const Ray& r );


  template <typename P0, typename E, typename P1>
  Ray::Ray( const P0& p0, E e, const P1& p1, const Collision_NS::XSegmentID& i_sid )
    : Ray{ p0, p1, i_sid, toFace( e ) }
  {
  }


  template <typename P0, typename P1>
  Ray::Ray( const P0& p0, const P1& p1, const Collision_NS::XSegmentID& i_sid, Collision_NS::Face f )
    : d_orbit{ orbit( f, p0 ) }
    , d_angle{ makeAngle( p1.toXFace( f ), p0.toXFace( f ) ) }
    , d_sid{ i_sid }
  {
  }
}