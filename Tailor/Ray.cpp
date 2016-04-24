#include "Ray.h"


size_t Tailor_NS::orbit( Collision_NS::Face f, Collision_NS::Vert o )
{
  size_t pos = 0;
  o = major( o );

  QEdge_NS::Edge i = o.e();
  do
  {
    if( id( f ) == id( Collision_NS::Face{ i } ) ) return pos;
    ++pos;
  }
  while( ( i = i.oNext() ) != o.e() );

  throw BadOrbit{ id( f ), id( o ) };
}


//  if face is l-face for major edge, return 0
size_t Tailor_NS::orbit( Collision_NS::Face f, Collision_NS::Edge o )
{
  o = major( o );
  
  if( id( f ) == id( Collision_NS::Face{ o.e() } ) )
    return 0;
  
  if( id( f ) == id( Collision_NS::Face{ o.e().sym() } ) )
    return 1;

  throw BadOrbit{ id( f ), id( o ) };
  
  //return o.isMajor() ^ ( Collision_NS::Face{ o.e() } == f );
}


size_t Tailor_NS::orbit( Collision_NS::Face f, Collision_NS::Face o )
{
  if( id( f ) != id( o ) ) throw BadOrbit{ id( f ), id( o ) };
  return 0;
}


Collision_NS::Face Tailor_NS::toFace( Collision_NS::Vert v )
{
  return major( Collision_NS::Face{ major( v ).e() } );
}


Collision_NS::Face Tailor_NS::toFace( Collision_NS::Edge e )
{
  return major( Collision_NS::Face{ major( e ).e() } );
}


Collision_NS::Face Tailor_NS::toFace( Collision_NS::Face f )
{
  return major( f );
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