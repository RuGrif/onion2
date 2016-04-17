#include "BaryCCW.h"
#include "../Math/Rational.h"


//  P = ( a * A + b * B + c * C ) / d , d = a + b + c
//  O = ( a'* A + b'* B + c'* C ) / d', d'= a'+ b'+ c'
//  P - O = 
//    ( a * d' + a' * d ) / ( d * d' ) * A +
//    ( b * d' + b' * d ) / ( d * d' ) * B +
//    ( c * d' + c' * d ) / ( d * d' ) * C


namespace Tailor_NS
{
  using BaryF = BaryCCW::BaryF;


  template <typename Int>
  class Angle
  {
  public:

    enum Q { Q1, Q2, Q3, Q4 };

    Angle( const Int& a, const Int& b, const Int& div ) : d{ div }
    {
      if( a < 0 )
        if( b < 0 ) { x = -a; y = -b; q = Q3; }
        else        { x =  b; y = -a; q = Q2; }
      else
        if( b < 0 ) { x = -b; y =  a; q = Q4; }
        else        { x =  a; y =  b; q = Q1; }
    }

    //  l.q < ...
    //  l.y / l.x < ...
    //  ( l.x * l.x + l.y * l.y ) / ( l.d * l.d ) < ...
    friend bool operator < ( const Angle& l, const Angle& r )
    {
      auto t = []( const Angle& a )
      {
        auto sqr = []( const auto& x ) { return Math_NS::prod( x, x ); };

        return std::make_tuple
        (
          a.q,
          Math_NS::makeRational( a.y, a.x ),
          Math_NS::makeRational( sqr( a.x ) + sqr( a.y ), sqr( a.d ) )
        );
      };

      return t( l ) < t( r );
    }

  private:
    
    Int x, y;   //  coordinate is { x / d, y / d } in face basis
    Int d;
    Q q;
  };


  template <typename Int>
  auto makeAngle( const Int& a, const Int& b, const Int& div )
  {
    return Angle<Int>{ a, b, div };
  }


  auto makeAngle( const BaryF& p, const BaryF& o, BaryF::Int( BaryF::*A ), BaryF::Int( BaryF::*B ) )
  {
    using Math_NS::prod;

    auto pd = p.a + p.b + p.c;
    auto od = o.a + o.b + o.c;
    
    return makeAngle(
      prod( p.*A, od ) - prod( o.*A, pd ),
      prod( p.*B, od ) - prod( o.*B, pd ),
      prod( od, pd ) );
  }


  auto makeAngleA( const BaryF& p, const BaryF& o ) { return makeAngle( p, o, &BaryF::b, &BaryF::c ); }
  auto makeAngleB( const BaryF& p, const BaryF& o ) { return makeAngle( p, o, &BaryF::c, &BaryF::a ); }
  auto makeAngleC( const BaryF& p, const BaryF& o ) { return makeAngle( p, o, &BaryF::a, &BaryF::b ); }
}


bool Tailor_NS::BaryCCW::operator()( const BaryF& l, const BaryF& r ) const
{
  return makeAngleC( l, o ) < makeAngleC( r, o );
}