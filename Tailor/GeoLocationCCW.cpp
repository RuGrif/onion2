#include "GeoLocationCCW.h"


Tailor_NS::GeoLocationCCW::GeoLocationCCW( const Collision_NS::XVert& v ) : d_faceCCW{ v }
{
  QEdge_NS::Edge e = v.e();
  do
  {
    Collision_NS::Face f{ e };
    d_baryCCW.emplace( id( f ), v.toXFace( f ) );
  }
  while( ( e = e.oNext() ) != v.e() );
}


Tailor_NS::GeoLocationCCW::GeoLocationCCW( const Collision_NS::XEdge& e ) : d_faceCCW{ e }
{
  for( QEdge_NS::Edge i : { e.e(), e.e().sym() } )
  {
    Collision_NS::Face f{ i };
    d_baryCCW.emplace( id( f ), e.toXFace( f ) );
  }
}


Tailor_NS::GeoLocationCCW::GeoLocationCCW( const Collision_NS::XFace& f ) : d_faceCCW{ f }
{
  d_baryCCW.emplace( id( f ), f );
}


bool Tailor_NS::GeoLocationCCW::operator() ( const GeoLocation& l, const GeoLocation& r ) const
{
  if( id( l.d_face ) == id( r.d_face ) )
  {
    const BaryCCW& bary = d_baryCCW.at( id( l.d_face ) );
    return bary( l.d_bary, r.d_bary ) || ( !bary( r.d_bary, l.d_bary ) && l.d_xid < r.d_xid );
  }
  else
  {
    return d_faceCCW( l.d_face, r.d_face );
  }
}