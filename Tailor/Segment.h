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


  class Segment
  {
  public:

    using SID = Collision_NS::XSegmentID;

    //  construct segment from intersection edge
    template <typename P0, typename P1>
    Segment( const P0& p0, Collision_NS::Face, const P1& p1, const Collision_NS::XSegmentID& );

    //  construct segment from real edge with intersection point on it
    Segment( Collision_NS::Edge );

    //  construct segment from real edge with intersection point in edge origin
    Segment( Collision_NS::Vert );

    friend bool operator < ( const Segment&, const Segment& );

  private:

    size_t    d_orbit;
    Angle     d_angle;
    SID       d_sid;
  };


  bool operator < ( const Segment& l, const Segment& r );


  template <typename P0, typename P1>
  Segment::Segment( const P0& p0, Collision_NS::Face f, const P1& p1, const Collision_NS::XSegmentID& i_sid )
    : d_orbit{ orbit( f, p0 ) }
    , d_angle{ makeAngle( p1.toXFace( f ), p0.toXFace( f ) ) }
    , d_sid{ i_sid }
  {
  }
}