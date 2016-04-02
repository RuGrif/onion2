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