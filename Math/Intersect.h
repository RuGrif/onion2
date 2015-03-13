#pragma once


#include "Vector3.h"
#include "Math.h"


namespace Math_NS
{
  using Vector = Vector3L;
  using Int = Vector::Type;

  //  register vertex-edge collsion
  //  edge UV
  struct VertEdge
  {
    virtual void operator() ( Int u, Int v, Int div ) = 0;
    virtual ~VertEdge() {}
  };

  //  register edge-edge collision
  //  first edge AB and second edge UV
  struct EdgeEdge
  {
    virtual void operator() ( Int a, Int b, Int u, Int v, Int div ) = 0;

    virtual VertEdge& A() = 0;
    virtual VertEdge& B() = 0;

    virtual ~EdgeEdge() {}
  };

  //  register face-edge collision
  //  triangle ABC and edge UV
  struct FaceEdge
  {
    virtual void operator() ( Int a, Int b, Int c, Int u, Int v, Int div ) = 0;

    virtual EdgeEdge& AB() = 0;
    virtual EdgeEdge& BC() = 0;
    virtual EdgeEdge& CA() = 0;

    virtual ~FaceEdge() {}
  };


  //  collides triangle ABC with edge UV
  MATH_API void intersect(
    const Vector& A, const Vector& B, const Vector& C,
    const Vector& U, const Vector& V,
    FaceEdge& );

  //  collides edge AB with edge UV
  MATH_API void intersect(
    const Vector& A, const Vector& B,
    const Vector& U, const Vector& V,
    EdgeEdge& );

  //  collides vert A with edge UV
  MATH_API void intersect(
    const Vector& A,
    const Vector& U, const Vector& V,
    VertEdge& );
}