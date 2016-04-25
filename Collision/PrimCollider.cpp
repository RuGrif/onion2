#include "PrimCollider.h"
#include "../Math/Solve.h"


bool Collision_NS::PrimCollider::collide( Vert a, Vert b, bool alter )
{
  if( grid( a.point() ) == grid( b.point() ) )
  {
    d_callback( XVert{ a }, XVert{ b }, alter );
    return true;
  }
  else
  {
    return false;
  }
}


bool Collision_NS::PrimCollider::collide( Vert v, Edge e, bool alter )
{
  //  A = u * U + v * V
  //  u + v = 1
  //
  //  v = 1 - u
  //  A = u * ( U - V ) + V
  //  u * ( V - U ) = V - A

  auto A = grid( v.point() );
  auto U = grid( e.U().point() );
  auto V = grid( e.V().point() );

  Int u{};

  if( auto div = Math_NS::solve( V - U, V - A, u ) )
  {
    if( u >= 0 && u <= div )
    {
      d_callback( XVert{ v }, XEdge{ e, u, div - u }, alter );
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    //  degenerated edge
    bool r = false;

    r |= collide( v, e.U(), alter );
    r |= collide( v, e.V(), alter );
    
    return r;
  }
}


bool Collision_NS::PrimCollider::collide( Vert v, Face f, bool alter )
{
  //  V = a * A + b * B + c * C
  //  a + b + c = 1
  //
  //  c = 1 - a - b
  //  V = a * ( A - C ) + b * ( B - C ) + C
  //  a * ( A - C ) + b * ( B - C ) = V - C

  auto V = grid( v.point() );
  auto A = grid( f.A().point() );
  auto B = grid( f.B().point() );
  auto C = grid( f.C().point() );

  Int a{}, b{};

  if( auto div = Math_NS::solve( A - C, B - C, V - C, a, b ) )
  {
    if( a >= 0 && b >= 0 && a <= div - b )
    {
      d_callback( XVert{ v }, XFace{ f, a, b, div - a - b }, alter );
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    //  degenerated face
    bool r = false;

    r |= collide( v, f.AB(), alter );
    r |= collide( v, f.BC(), alter );
    r |= collide( v, f.CA(), alter );

    return r;
  }
}


bool Collision_NS::PrimCollider::collide( Edge e1, Edge e2, bool alter )
{
  //  u1 * U1 + v1 * V1 = u2 * U2 + v2 * V2
  //  u1 + v1 = 1
  //  u2 + v2 = 1
  //
  //  v1 = 1 - u1
  //  v2 = 1 - u2
  //  u1 * ( U1 - V1 ) + V1 = u2 * ( U2 - V2 ) + V2
  //  u1 * ( U1 - V1 ) + u2 * ( V2 - U2 ) = V2 - V1

  auto U1 = grid( e1.U().point() );
  auto V1 = grid( e1.V().point() );
  auto U2 = grid( e2.U().point() );
  auto V2 = grid( e2.V().point() );

  Int u1{}, u2{};

  if( auto div = Math_NS::solve( U1 - V1, V2 - U2, V2 - V1, u1, u2 ) )
  {
    if( u1 >= 0 && u1 <= div && u2 >= 0 && u2 <= div )
    {
      d_callback( XEdge{ e1, u1, div - u1 }, XEdge{ e2, u2, div - u2 }, alter );
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    //  parallel edges
    bool r = false;

    r |= collide( e1.U(), e2, alter );
    r |= collide( e1.V(), e2, alter );
    r |= collide( e2.U(), e1, !alter );
    r |= collide( e2.V(), e1, !alter );

    return r;
  }
}


bool Collision_NS::PrimCollider::collide( Edge e, Face f, bool alter )
{
  //  u * U + v * V = a * A + b * B + c * C
  //  u + v = 1
  //  a + b + c = 1
  //
  //  v = 1 - u
  //  c = 1 - a - b
  //  u * ( U - V ) + V = a * ( A - C ) + b * ( B - C ) + C
  //  u * ( V - U ) + a * ( A - C ) + b * ( B - C ) = V - C

  auto U = grid( e.U().point() );
  auto V = grid( e.V().point() );
  auto A = grid( f.A().point() );
  auto B = grid( f.B().point() );
  auto C = grid( f.C().point() );

  Int u{}, a{}, b{};

  if( auto div = Math_NS::solve( V - U, A - C, B - C, V - C, u, a, b ) )
  {
    if( u >= 0 && u <= div && a >= 0 && b >= 0 && a <= div - b )
    {
      d_callback( XEdge{ e, u, div - u }, XFace{ f, a, b, div - a - b }, alter );
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    //  edge parallel to face
    ++d_ffOverlapCounter;

    bool r = false;

    r |= collide( e, f.AB(), alter );
    r |= collide( e, f.BC(), alter );
    r |= collide( e, f.CA(), alter );
    r |= collide( e.U(), f, alter );
    r |= collide( e.V(), f, alter );

    return r;
  }
}


bool Collision_NS::PrimCollider::operator() ( Face a, Face b )
{
  d_ffOverlapCounter = 0;

  bool r = false;
  
  if( a.AB().isMajor() ) r |= collide( a.AB(), b, false );
  if( a.BC().isMajor() ) r |= collide( a.BC(), b, false );
  if( a.CA().isMajor() ) r |= collide( a.CA(), b, false );
  if( b.AB().isMajor() ) r |= collide( b.AB(), a, true );
  if( b.BC().isMajor() ) r |= collide( b.BC(), a, true );
  if( b.CA().isMajor() ) r |= collide( b.CA(), a, true );

  if( d_ffOverlapCounter == 6 && r ) d_callback.markOverlap( a, b );

  return r;
}