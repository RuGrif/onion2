#include "Collider.h"
#include "..\Math\Solve.h"
#include <memory>


namespace Collision_NS
{
  using Int = Collider::Int;

  class Intersection : public Node
  {
  public:

    Intersection( std::unique_ptr<Prim> i_alpha, std::unique_ptr<Prim> i_beta, const Math_NS::Vector3D& i_intersection )
      : d_alpha( std::move( i_alpha ) ), d_beta( std::move( i_beta ) )
      , d_intersection( i_intersection )
    {}

    virtual Prim&                 alpha() const override { return *d_alpha; }
    virtual Prim&                 beta() const override { return *d_beta; }

    virtual Math_NS::Vector3D     intersection() const override { return d_intersection; }

  private:
    
    std::unique_ptr<Prim>         d_alpha;
    std::unique_ptr<Prim>         d_beta;
    Math_NS::Vector3D             d_intersection;
  };


  std::unique_ptr<Prim> makePrim( Vert v )
  {
    return v.clone();
  }

  std::unique_ptr<Prim> makePrim( Edge e, Int u, Int v )
  {
    if( u == 0 ) return makePrim( e.V() );
    if( v == 0 ) return makePrim( e.U() );
    return e.clone();
  }

  std::unique_ptr<Prim> makePrim( Face f, Int a, Int b, Int c )
  {
    if( a == 0 ) return makePrim( f.BC(), b, c );
    if( b == 0 ) return makePrim( f.CA(), c, a );
    if( c == 0 ) return makePrim( f.AB(), a, b );
    return f.clone();
  }


  std::unique_ptr<Intersection> makeIntersection(
    std::unique_ptr<Prim>&& i_alpha,
    std::unique_ptr<Prim>&& i_beta,
    const Math_NS::Vector3D& i_intersection,
    bool i_alter )
  {
    return i_alter
      ? std::make_unique<Intersection>( std::move( i_beta ), std::move( i_alpha ), i_intersection )
      : std::make_unique<Intersection>( std::move( i_alpha ), std::move( i_beta ), i_intersection );
  }
}


bool Collision_NS::Collider::collide( Vert a, Vert b, bool alter )
{
  if( grid( a.point() ) == grid( b.point() ) )
  {
    Math_NS::Vector3D i = ( a.point() + b.point() ) / 2.;    
    d_graph.push( makeIntersection( makePrim( a ), makePrim( b ), i, alter ) );
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
    d_graph.push( makeIntersection( makePrim( v ), makePrim( e, u, div - u ), v.point(), alter ) );
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
    d_graph.push( makeIntersection( makePrim( v ), makePrim( f, a, b, div - a - b ), v.point(), alter ) );
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

  if( div > 0 && u1 >= 0 && u1 <= div && u2 >= 0 && u2 <= div )
  {
    Math_NS::Vector3D i1 = ( static_cast<double>( u1 ) * e1.U().point() + static_cast<double>( div - u1 ) * e1.V().point() ) / static_cast<double>( div );
    Math_NS::Vector3D i2 = ( static_cast<double>( u2 ) * e2.U().point() + static_cast<double>( div - u2 ) * e2.V().point() ) / static_cast<double>( div );

    d_graph.push( makeIntersection( makePrim( e1, u1, div - u1 ), makePrim( e2, u2, div - u2 ), ( i1 + i2 ) / 2., alter ) );

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
    Math_NS::Vector3D i = ( static_cast<double>( u ) * e.U().point() + static_cast<double>( div - u ) * e.V().point() ) / static_cast<double>( div );
    d_graph.push( makeIntersection( makePrim( e, u, div - u ), makePrim( f, a, b, div - a - b ), i, alter ) );
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