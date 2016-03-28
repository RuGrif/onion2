#include "Intersection.h"


void Collision_NS::Intersection::operator() ( const XVert& x, const XVert& y, bool a )
{
  add( x, y, a );
}


void Collision_NS::Intersection::operator() ( const XVert& x, const XEdge& y, bool a )
{
  if( y.u == 0 ) return operator() ( x, XVert{ y.V() }, a );
  if( y.v == 0 ) return operator() ( x, XVert{ y.U() }, a );
  return add( x, y, a );
}


void Collision_NS::Intersection::operator() ( const XVert& x, const XFace& y, bool a )
{
  if( y.a == 0 ) return operator() ( x, XEdge{ y.BC(), y.b, y.c }, a );
  if( y.b == 0 ) return operator() ( x, XEdge{ y.CA(), y.c, y.a }, a );
  if( y.c == 0 ) return operator() ( x, XEdge{ y.AB(), y.a, y.b }, a );
  return add( x, y, a );
}


void Collision_NS::Intersection::operator() ( const XEdge& x, const XEdge& y, bool a )
{
  if( x.u == 0 ) return operator() ( XVert{ x.V() }, y, a );
  if( x.v == 0 ) return operator() ( XVert{ x.U() }, y, a );
  if( y.u == 0 ) return operator() ( XVert{ y.V() }, x, !a );
  if( y.v == 0 ) return operator() ( XVert{ y.U() }, x, !a );
  return add( x, y, a );
}


void Collision_NS::Intersection::operator() ( const XEdge& x, const XFace& y, bool a )
{
  if( x.u == 0 ) return operator() ( XVert{ x.V() }, y, a );
  if( x.v == 0 ) return operator() ( XVert{ x.U() }, y, a );
  if( y.a == 0 ) return operator() ( x, XEdge{ y.BC(), y.b, y.c }, a );
  if( y.b == 0 ) return operator() ( x, XEdge{ y.CA(), y.c, y.a }, a );
  if( y.c == 0 ) return operator() ( x, XEdge{ y.AB(), y.a, y.b }, a );
  return add( x, y, a );
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


const Math_NS::Vector3D Collision_NS::point( const XVert& x, const XVert& y ) { return ( point( x ) + point( y ) ) / 2.; }
const Math_NS::Vector3D Collision_NS::point( const XVert& x, const XEdge& y ) { return point( x ); }
const Math_NS::Vector3D Collision_NS::point( const XVert& x, const XFace& y ) { return point( x ); }
const Math_NS::Vector3D Collision_NS::point( const XEdge& x, const XVert& y ) { return point( y ); }
const Math_NS::Vector3D Collision_NS::point( const XEdge& x, const XEdge& y ) { return ( point( x ) + point( y ) ) / 2.; }
const Math_NS::Vector3D Collision_NS::point( const XEdge& x, const XFace& y ) { return point( x ); }
const Math_NS::Vector3D Collision_NS::point( const XFace& x, const XVert& y ) { return point( y ); }
const Math_NS::Vector3D Collision_NS::point( const XFace& x, const XEdge& y ) { return point( y ); }