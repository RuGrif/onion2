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
  for( QEdge_NS::Edge i : { e.e(), e.e().sym() } )
  {
    d_order.emplace( id( Collision_NS::Face{ i } ), d_order.size() );
  }
}


Tailor_NS::FaceCCW::FaceCCW( Collision_NS::Face f )
{
  d_order.emplace( id( f ), d_order.size() );
}


bool Tailor_NS::FaceCCW::operator()( const Collision_NS::Face& l, const Collision_NS::Face& r ) const
{
  return d_order.at( id( l ) ) < d_order.at( id( r ) );
}