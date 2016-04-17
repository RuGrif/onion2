#pragma once


//
//  CCW points sorting predicate
//


#include "../Collision/Barycentric.h"
#include "../Math/Rational.h"


namespace Tailor_NS
{
  using Dot = Collision_NS::BaryF;


  class Angle
  {
  public:

    using Int = decltype( Math_NS::prod( std::declval<Math_NS::Vector3L::Type>(), std::declval<Math_NS::Vector3L::Type>() ) );

    enum Q { Q1, Q2, Q3, Q4 };

  public:

    //  construct zero angle
    Angle() : x{ 1 }, y{ 0 }, d{ 1 }, q{ Q1 } {}

    Angle( const Int& a, const Int& b, const Int& div );

    friend bool operator < ( const Angle&, const Angle& );

  private:

    Int x, y;   //  coordinate is { x / d, y / d } in face basis
    Int d;
    Q q;
  };


  bool operator < ( const Angle&, const Angle& );


  Angle makeAngleA( const Dot& p, const Dot& o );
  Angle makeAngleB( const Dot& p, const Dot& o );
  Angle makeAngleC( const Dot& p, const Dot& o );
}