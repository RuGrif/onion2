#include "Angle.h"


Tailor_NS::Angle::Angle( const Int& a, const Int& b, const Int& div ) : d{ div }
{
  if( a < 0 )
    if( b < 0 ) { x = -a; y = -b; q = Q3; }
    else { x = b; y = -a; q = Q2; }
  else
    if( b < 0 ) { x = -b; y = a; q = Q4; }
    else { x = a; y = b; q = Q1; }
}


//  l.q < ...
//  l.y / l.x < ...
//  ( l.x * l.x + l.y * l.y ) / ( l.d * l.d ) < ...
bool Tailor_NS::operator < ( const Angle& l, const Angle& r )
{
  auto t = []( const Angle& a )
  {
    using Math_NS::prod;
    using Math_NS::makeRational;

    return std::make_tuple
    (
      a.q,
      makeRational( a.y, a.x ),
      makeRational( prod( a.x, a.x ) + prod( a.y, a.y ), prod( a.d, a.d ) )
    );
  };

  return t( l ) < t( r );
}


namespace
{
  using namespace Tailor_NS;

  //  P = ( a * A + b * B + c * C ) / d , d = a + b + c
  //  O = ( a'* A + b'* B + c'* C ) / d', d'= a'+ b'+ c'
  //  P - O = 
  //    ( a * d' + a' * d ) / ( d * d' ) * A +
  //    ( b * d' + b' * d ) / ( d * d' ) * B +
  //    ( c * d' + c' * d ) / ( d * d' ) * C
  Angle makeAngleX( const Dot& p, const Dot& o, Dot::Int( Dot::*A ), Dot::Int( Dot::*B ) )
  {
    using Math_NS::prod;

    auto pd = p.a + p.b + p.c;
    auto od = o.a + o.b + o.c;

    return
    {
      prod( p.*A, od ) - prod( o.*A, pd ),
      prod( p.*B, od ) - prod( o.*B, pd ),
      prod( od, pd )
    };
  }
}


Tailor_NS::Angle Tailor_NS::makeAngleA( const Dot& p, const Dot& o ) { return makeAngleX( p, o, &Dot::b, &Dot::c ); }
Tailor_NS::Angle Tailor_NS::makeAngleB( const Dot& p, const Dot& o ) { return makeAngleX( p, o, &Dot::c, &Dot::a ); }
Tailor_NS::Angle Tailor_NS::makeAngleC( const Dot& p, const Dot& o ) { return makeAngleX( p, o, &Dot::a, &Dot::b ); }