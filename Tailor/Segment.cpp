#include "Segment.h"


size_t Tailor_NS::orbit( Collision_NS::Face f, Collision_NS::Vert o )
{
  size_t fpos = 0;  //  index of edge with e.l == f in edge loop around o
  size_t zpos = 0;  //  index of origin edge in edge loop around o

  QEdge_NS::Edge e = o.e();

  size_t orig = id( Collision_NS::Edge{ e } );

  size_t i = 1;

  for( ; ( e = e.oNext() ) != o.e(); ++i )
  {
    size_t cur = id( Collision_NS::Edge{ e } );

    if( cur < orig )
    {
      zpos = i;
      orig = cur;
    }
    
    if( Collision_NS::Face{ e } == f )
    {
      fpos = i;
    }
  }

  return fpos < zpos ? i + fpos - zpos : fpos - zpos;
}


size_t Tailor_NS::orbit( Collision_NS::Face f, Collision_NS::Edge o )
{
  //  if face is l-face for major edge, return 0
  //
  //  Major ^ equal -> false -> 0
  //  Major ^ diffr -> true  -> 1
  //  Minor ^ equal -> true  -> 1
  //  Minot ^ diffr -> false -> 0
  return o.isMajor() ^ ( Collision_NS::Face{ o.e() } == f );
}


size_t Tailor_NS::orbit( Collision_NS::Face f, Collision_NS::Face o )
{
  return 0;
}


Tailor_NS::Ray::Ray( Collision_NS::Edge e )
  : d_orbit{ e.isMajor() ? 0u : 1u }
  , d_angle{}
  , d_sid{}
{

}


Tailor_NS::Ray::Ray( Collision_NS::Vert v )
  : d_orbit{ orbit( Collision_NS::Face{ v.e() }, v ) }
  , d_angle{}
  , d_sid{}
{

}


bool Tailor_NS::operator < ( const Ray& l, const Ray& r )
{
  return std::tie( l.d_orbit, l.d_angle, l.d_sid ) < std::tie( r.d_orbit, r.d_angle, r.d_sid );
}