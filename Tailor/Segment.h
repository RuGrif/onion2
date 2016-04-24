#pragma once


//
//  intersection segment with defined operator <
//


#include "Angle.h"
#include "../Collision/Primitive.h"
#include "../Collision/XPoint.h"


namespace Tailor_NS
{
  //  defines order number of face f around orbit o
  size_t orbit( Collision_NS::Face f, Collision_NS::Vert o ); //  count from edge with min id
  size_t orbit( Collision_NS::Face f, Collision_NS::Edge o ); //  major face < minor face
  size_t orbit( Collision_NS::Face f, Collision_NS::Face o );


  class Ray
  {
  public:

    using SID = Collision_NS::XSegmentID;

    //  construct segment from intersection edge
    template <typename P0, typename P1>
    Ray( const P0& p0, Collision_NS::Face, const P1& p1, const Collision_NS::XSegmentID& );

    //  construct segment from real edge with intersection point on it
    Ray( Collision_NS::Edge );

    //  construct segment from real edge with intersection point in vertex in edge origin
    Ray( Collision_NS::Vert );

    friend bool operator < ( const Ray&, const Ray& );

    const SID& sid() const { return d_sid; }

  private:

    size_t    d_orbit;
    Angle     d_angle;
    SID       d_sid;
  };


  bool operator < ( const Ray& l, const Ray& r );


  template <typename P0, typename P1>
  Ray::Ray( const P0& p0, Collision_NS::Face f, const P1& p1, const Collision_NS::XSegmentID& i_sid )
    : d_orbit{ orbit( f, p0 ) }
    , d_angle{ makeAngle( p1.toXFace( f ), p0.toXFace( f ) ) }
    , d_sid{ i_sid }
  {
  }
}