#include "XPoint.h"


Collision_NS::XEdge Collision_NS::XVert::toXEdge( Edge e ) const
{
  if( *this == e.U() ) return{ e, 1, 0 };
  if( *this == e.V() ) return{ e, 0, 1 };
  throw BadUpcast( id( *this ), id( e ) );
}


Collision_NS::XFace Collision_NS::XVert::toXFace( Face f ) const
{
  if( *this == f.A() ) return{ f, 1, 0, 0 };
  if( *this == f.B() ) return{ f, 0, 1, 0 };
  if( *this == f.C() ) return{ f, 0, 0, 1 };
  throw BadUpcast( id( *this ), id( f ) );
}


Collision_NS::XFace Collision_NS::XEdge::toXFace( Face f ) const
{
  if( *this == f.AB() ) return{ f, u, v, 0 };
  if( *this == f.BC() ) return{ f, 0, u, v };
  if( *this == f.CA() ) return{ f, v, 0, u };
  throw BadUpcast( id( *this ), id( f ) );
}


Collision_NS::XFace Collision_NS::XFace::toXFace( Face f ) const
{
  if( e() == f.e() ) return *this;
  //if( id( *this ) == id( f ) )
  //{
  //  if( id( A() ) == id( f.A() ) ) return{ f, a, b, c };
  //  if( id( B() ) == id( f.A() ) ) return{ f, b, c, a };
  //  if( id( C() ) == id( f.A() ) ) return{ f, c, a, b };
  //}
  throw BadUpcast( id( *this ), id( f ) );
}


const Math_NS::Vector3D Collision_NS::point( const XVert& v )
{
  return v.point();
}


const Math_NS::Vector3D Collision_NS::point( const XEdge& e )
{
  const double u = static_cast<double>( e.u );
  const double v = static_cast<double>( e.v );
  return ( u * e.U().point() + v * e.V().point() ) / ( u + v );
}


Math_NS::Vector3D Collision_NS::point( const XVert& x, const XVert& y ) { return ( point( x ) + point( y ) ) / 2.; }
Math_NS::Vector3D Collision_NS::point( const XVert& x, const XEdge& y ) { return point( x ); }
Math_NS::Vector3D Collision_NS::point( const XVert& x, const XFace& y ) { return point( x ); }
Math_NS::Vector3D Collision_NS::point( const XEdge& x, const XVert& y ) { return point( y ); }
Math_NS::Vector3D Collision_NS::point( const XEdge& x, const XEdge& y ) { return ( point( x ) + point( y ) ) / 2.; }
Math_NS::Vector3D Collision_NS::point( const XEdge& x, const XFace& y ) { return point( x ); }
Math_NS::Vector3D Collision_NS::point( const XFace& x, const XVert& y ) { return point( y ); }
Math_NS::Vector3D Collision_NS::point( const XFace& x, const XEdge& y ) { return point( y ); }
