#pragma once


#include "Vector3.h"


namespace Math_NS
{
  //  solve linear system
  //    a * A + b * B + c * C = r * R
  //  where r is return value
  //  in degenerated case r is 0
  //  in normal case r > 0
  Math_NS::Vector3L::Type solve(
    const Math_NS::Vector3L& A,
    const Math_NS::Vector3L& B,
    const Math_NS::Vector3L& C,
    const Math_NS::Vector3L& R,
    Math_NS::Vector3L::Type& a,
    Math_NS::Vector3L::Type& b,
    Math_NS::Vector3L::Type& c );


  //  solve linear system
  //    a * A + b * B = r * R
  //  where r is return value
  //  in degenerated case r is 0
  //  in normal case r > 0
  Math_NS::Vector3L::Type solve(
    const Math_NS::Vector3L& A,
    const Math_NS::Vector3L& B,
    const Math_NS::Vector3L& R,
    Math_NS::Vector3L::Type& a,
    Math_NS::Vector3L::Type& b );


  //  solve linear system
  //    a * A = r * R
  //  where r is return value
  //  in degenerated case r is 0
  //  in normal case r > 0
  Math_NS::Vector3L::Type solve(
    const Math_NS::Vector3L& A,
    const Math_NS::Vector3L& R,
    Math_NS::Vector3L::Type& a );
}