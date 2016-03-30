#pragma once


#include "../QEdge/Data.h"


namespace Tailor_NS
{
  template <typename A, typename B>
  class XPointData : public QEdge_NS::VertData
  {
  public:

    XPointData( const A& a, const B& b ) : a{ a }, b{ b } {}

    virtual const Math_NS::Vector3D point() const override { return Collision_NS::point( a, b ); }

  private:

    A a;
    B b;
  };
}