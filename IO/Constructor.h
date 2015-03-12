#pragma once


#include "..\QEdge\Shape.h"
#include "..\Math\Hash.h"
#include <unordered_map>


namespace IO_NS
{
  class Constructor
  {
  public:

    Constructor( QEdge_NS::Shape& );

    void addTriangle( const Math_NS::Vector3F& a, const Math_NS::Vector3F& b, const Math_NS::Vector3F& c );

  private:

    using Segment = std::pair<Math_NS::Vector3F, Math_NS::Vector3F>;

    QEdge_NS::Edge getOrConstructEdge( const Math_NS::Vector3F& a, const Math_NS::Vector3F& b );
    void stitch( QEdge_NS::Edge a, QEdge_NS::Edge b );
    void makeVertex( QEdge_NS::Vert& v, const Math_NS::Vector3F& p );

  private:

    std::unordered_map<Segment, QEdge_NS::Edge>   d_edges;
    QEdge_NS::Shape&                              d_shape;
  };
}