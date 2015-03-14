#include "Collider.h"
#include "..\Math\Solve.h"
#include <memory>


namespace Collision_NS
{
  using Int = Collider::Int;

  namespace
  {
    std::unique_ptr<Prim> makePrim( Vert v )
    {
      return std::make_unique<Vert>( v );
    }

    std::unique_ptr<Prim> makePrim( Edge e, Int u, Int v )
    {
      if( u == 0 ) return makePrim( e.V() );
      if( v == 0 ) return makePrim( e.U() );
      return std::make_unique<Edge>( e );
    }

    std::unique_ptr<Prim> makePrim( Face f, Int a, Int b, Int c )
    {
      if( a == 0 ) return makePrim( f.BC(), b, c );
      if( b == 0 ) return makePrim( f.CA(), c, a );
      if( c == 0 ) return makePrim( f.AB(), a, b );
      return std::make_unique<Face>( f );
    }
  }
}


bool Collision_NS::Collider::collide( Vert a, Vert b, bool alter )
{
  if( grid( a.point() ) == grid( b.point() ) )
  {
    Node node( makePrim( a ), makePrim( b ) );
    
    if( alter ) node.alter();
    
    graph.push( std::move( node ) );
    
    return true;
  }
  else
  {
    return false;
  }
}


bool Collision_NS::Collider::collide( Vert v, Edge e, bool alter )
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

  auto div = Math_NS::solve( V - U, V - A, u );

  if( div > 0 && u >= 0 && u <= div )
  {
    Node node( makePrim( v ), makePrim( e, u, div - u ) );

    if( alter ) node.alter();

    graph.push( std::move( node ) );

    return true;
  }
  else
  {
    //  degenerated edge
    bool r1 = collide( v, e.U(), alter );
    bool r2 = collide( v, e.V(), alter );
    
    return r1 || r2;
  }
}


bool Collision_NS::Collider::collide( Vert v, Face f, bool alter )
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

  auto div = Math_NS::solve( A - C, B - C, V - C, a, b );

  if( div > 0 && a >= 0 && b >= 0 && a <= div - b )
  {
    Node node( makePrim( v ), makePrim( f, a, b, div - a - b ) );

    if( alter ) node.alter();

    graph.push( std::move( node ) );

    return true;
  }
  else
  {
    //  degenerated face
    bool r1 = collide( v, f.AB(), alter );
    bool r2 = collide( v, f.BC(), alter );
    bool r3 = collide( v, f.CA(), alter );

    return r1 || r2 || r3;
  }
}


bool Collision_NS::Collider::collide( Edge e1, Edge e2, bool alter )
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

  auto div = Math_NS::solve( U1 - V1, V2 - U2, V2 - V1, u1, u2 );

  if( div > 0 && u1 >= 0 && u1 >= div - u1 && u2 >= 0 && u2 <= div - u2 )
  {
    Node node( makePrim( e1, u1, div - u1 ), makePrim( e2, u2, div - u2 ) );

    if( alter ) node.alter();

    graph.push( std::move( node ) );

    return true;
  }
  else
  {
    //  parallel edges
    bool r1 = collide( e1.U(), e2, alter );
    bool r2 = collide( e1.V(), e2, alter );
    bool r3 = collide( e2.U(), e1, !alter );
    bool r4 = collide( e2.V(), e1, !alter );

    return r1 || r2 || r3 || r4;
  }
}


bool Collision_NS::Collider::collide( Edge e, Face f, bool alter )
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

  auto div = Math_NS::solve( V - U, A - C, B - C, V - C, u, a, b );

  if( div > 0 && u >= 0 && u <= div && a >= 0 && b >= 0 && a <= div - b )
  {
    Node node( makePrim( e, u, div - u ), makePrim( f, a, b, div - a - b ) );

    if( alter ) node.alter();

    graph.push( std::move( node ) );

    return true;
  }
  else
  {
    //  edge parallel to face
    bool r1 = collide( e, f.AB(), alter );
    bool r2 = collide( e, f.BC(), alter );
    bool r3 = collide( e, f.CA(), alter );
    bool r4 = collide( e.U(), f, alter );
    bool r5 = collide( e.V(), f, alter );

    return r1 || r2 || r3 || r4 || r5;
  }
}