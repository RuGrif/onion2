#include "FaceCCW.h"


Tailor_NS::FaceCCW::FaceCCW( Collision_NS::Vert v )
{
  QEdge_NS::Edge e = v.e();
  
  do
  {
    d_order.emplace( id( Collision_NS::Face{ e } ), d_order.size() );
  }
  while( ( e = e.oNext() ) != v.e() );
}


Tailor_NS::FaceCCW::FaceCCW( Collision_NS::Edge e )
{
  d_order.emplace( id( Collision_NS::Face{ e.e() } ), 0 );
  d_order.emplace( id( Collision_NS::Face{ e.e().sym() } ), 1 );
}


Tailor_NS::FaceCCW::FaceCCW( Collision_NS::Face f )
{
  d_order.emplace( id( f ), 0 );
}


bool Tailor_NS::FaceCCW::operator()( const Collision_NS::Face& l, const Collision_NS::Face& r ) const
{
  return d_order.at( id( l ) ) < d_order.at( id( r ) );
}