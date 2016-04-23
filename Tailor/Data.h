#pragma once


#include "../QEdge/Data.h"


namespace Tailor_NS
{
  template <typename A, typename B>
  class XPointData : public QEdge_NS::VertData
  {
  public:

    XPointData( const A& a, const B& b )
      : d_point{ Collision_NS::point( a, b ) }
      , d_idA{ id( a ) }
      , d_idB{ id( b ) }
    {}

    virtual const Math_NS::Vector3D point() const override { return d_point; }

  private:

    Math_NS::Vector3D d_point;
    size_t            d_idA;
    size_t            d_idB;
  };


  template <typename A, typename B>
  void resetXPointData( QEdge_NS::Vert& v, const A& a, const B& b )
  {
    v.reset<XPointData<A, B>>( a, b );
  }


  template <typename A, typename B>
  void resetXPointData( QEdge_NS::Edge e, const A& a, const B& b )
  {
    resetXPointData( e.o(), a, b );
  }


  template <typename A, typename B>
  void setXPointData( QEdge_NS::Edge e, const A& a, const B& b )
  {
    if( !e.o() ) resetXPointData( e, a, b );
  }
}