#pragma once


#include "..\QEdge\Shape.h"
#include "..\Math\Hash.h"
#include <unordered_map>


namespace IO_NS
{
  class Constructor
  {
  public:

    void addTriangle( const Math_NS::Vector3F& a, const Math_NS::Vector3F& b, const Math_NS::Vector3F& c );
    
    static QEdge_NS::Shape&& getShape( Constructor&& );

  private:

    using Segment = std::pair<Math_NS::Vector3F, Math_NS::Vector3F>;

    QEdge_NS::Edge getOrConstructEdge( const Math_NS::Vector3F& a, const Math_NS::Vector3F& b );

  private:

    std::unordered_map<Segment, QEdge_NS::Edge>   d_edges;
    QEdge_NS::Shape                               d_shape;
  };
}