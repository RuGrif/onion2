#pragma once


#include "Vector3.h"
#include "Math.h"


namespace Math_NS
{
  namespace IS_NS //  intersection traits
  {
    using Vec = Vector3L;
    using Int = Vec::Type;
  }

  //  register vertex-edge collsion
  //  edge UV
  struct VertEdge
  {
    using Int = IS_NS::Int;
    using Vec = IS_NS::Vec;

    virtual void operator() ( Int u, Int v, Int div ) = 0;

    virtual ~VertEdge() {}
  };

  //  register edge-edge collision
  //  first edge AB and second edge UV
  struct EdgeEdge
  {
    using Int = IS_NS::Int;
    using Vec = IS_NS::Vec;

    virtual void operator() ( Int a, Int b, Int u, Int v, Int div ) = 0;

    virtual VertEdge& A() = 0;
    virtual VertEdge& B() = 0;

    virtual ~EdgeEdge() {}
  };


  //  register face-edge collision
  //  triangle ABC and edge UV
  struct FaceEdge
  {
    using Int = IS_NS::Int;
    using Vec = IS_NS::Vec;

    virtual void operator() ( Int a, Int b, Int c, Int u, Int v, Int div ) = 0;

    virtual EdgeEdge& AB() = 0;
    virtual EdgeEdge& BC() = 0;
    virtual EdgeEdge& CA() = 0;

    virtual ~FaceEdge() {}
  };


  //  collides triangle ABC with edge UV
  MATH_API void intersect(
    const IS_NS::Vec& A, const IS_NS::Vec& B, const IS_NS::Vec& C,
    const IS_NS::Vec& U, const IS_NS::Vec& V,
    FaceEdge& );

  //  collides edge AB with edge UV
  MATH_API void intersect(
    const IS_NS::Vec& A, const IS_NS::Vec& B,
    const IS_NS::Vec& U, const IS_NS::Vec& V,
    EdgeEdge& );

  //  collides vert A with edge UV
  MATH_API void intersect(
    const IS_NS::Vec& A,
    const IS_NS::Vec& U, const IS_NS::Vec& V,
    VertEdge& );
}