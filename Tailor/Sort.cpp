#include "Sort.h"


//  P = ( a * A + b * B + c * C ) / d , d = a + b + c
//  O = ( a'* A + b'* B + c'* C ) / d', d'= a'+ b'+ c'
//  P - O = 
//    ( a * d' + a' * d ) / ( d * d' ) * A +
//    ( a * d' + a' * d ) / ( d * d' ) * B +
//    ( a * d' + a' * d ) / ( d * d' ) * C


namespace Tailor_NS
{
  using Point = BarycentricCCW::Point;


  template <typename Int>
  struct Rational
  {
    Int n;  //  nominator
    Int d;  //  denominator

    //Rational( Int&& n, Int&& d ) : n{ std::forward<Int>( n ) }, d{ std::forward<Int>( d ) } {}

    friend bool operator < ( const Rational& l, const Rational& r )
    {
      return Math_NS::prod( l.n, r.d ) < Math_NS::prod( r.n, l.d );
    }
  };


  template <typename Int>
  auto makeRational( Int&& n, Int&& d )
  {
    return Rational<Int>{ std::forward<Int>( n ), std::forward<Int>( d ) };
  }


  template <typename Int>
  class Angle
  {
  public:

    enum Q { Q1, Q2, Q3, Q4 };

    Angle( const Int& a, const Int& b, const Int& div ) : d{ div }
    {
      if( a > 0 )
        if( b > 0 ) { x =  a; y =  b; q = Q1; }
        else        { x = -b; y =  a; q = Q4; }
      else
        if( b > 0 ) { x =  b; y = -a; q = Q2; }
        else        { x = -a; y = -b; q = Q3; }
    }

    //  l.q < ...
    //  l.x / l.y < ...
    //  ( l.x * l.x + l.y * l.y ) / ( l.d * l.d ) < ...
    friend bool operator < ( const Angle& l, const Angle& r )
    {
      auto t = []( const Angle& a )
      {
        auto sqr = []( const auto& x ) { return Math_NS::prod( x, x ); };

        return std::make_tuple
        (
          a.q,
          makeRational( a.x, a.y ),
          makeRational( sqr( a.x ) + sqr( a.y ), sqr( a.d ) )
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


  auto makeAngle( const Point& p, const Point& o )
  {
    using Math_NS::prod;

    auto pd = p.a + p.b + p.c;
    auto od = o.a + o.b + o.c;
    
    return makeAngle(
      prod( p.a, od ) - prod( o.a, pd ),
      prod( p.b, od ) - prod( o.b, pd ),
      prod( od, pd ) );
  }
}


bool Tailor_NS::BarycentricCCW::operator()( const Point& l, const Point& r ) const
{
  return makeAngle( l, o ) < makeAngle( r, o );
}