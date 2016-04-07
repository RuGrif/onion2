#include "XEdgeCCW.h"


Tailor_NS::XEdgeCCW::XEdgeCCW( const Collision_NS::XVert& v ) : d_faceCCW{ v }
{
  QEdge_NS::Edge e = v.e();
  do
  {
    Collision_NS::Face f{ e };
    d_baryCCW.emplace( id( f ), v.toXFace( f ) );
  }
  while( ( e = e.oNext() ) != v.e() );
}


Tailor_NS::XEdgeCCW::XEdgeCCW( const Collision_NS::XEdge& e ) : d_faceCCW{ e }
{
  for( QEdge_NS::Edge i : { e.e(), e.e().sym() } )
  {
    Collision_NS::Face f{ i };
    d_baryCCW.emplace( id( f ), e.toXFace( f ) );
  }
}


Tailor_NS::XEdgeCCW::XEdgeCCW( const Collision_NS::XFace& f ) : d_faceCCW{ f }
{
  d_baryCCW.emplace( id( f ), f );
}


bool Tailor_NS::XEdgeCCW::operator() ( const Collision_NS::XFace& l, const Collision_NS::XFace& r ) const
{
  return id( l ) == id( r ) ? d_baryCCW.at( id( l ) )( l, r ) : d_faceCCW( l, r );
}