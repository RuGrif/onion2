#pragma once


#include "Shape.h"
#include <vector>
#include "QEdge.h"


namespace QEdge_NS
{
  QEDGE_API std::vector<Edge> allVerts( const Shape& );
  QEDGE_API std::vector<Edge> allEdges( const Shape& );
  QEDGE_API std::vector<Edge> allFaces( const Shape& );
}