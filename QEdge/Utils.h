#pragma once


#include "Shape.h"
#include <vector>
#include "../Math/Box3.h"


namespace QEdge_NS
{
  std::vector<Edge> allVerts( const Shape& );
  std::vector<Edge> allEdges( const Shape& );
  std::vector<Edge> allFaces( const Shape& );

  Math_NS::Box3D box( const std::vector<Edge>& i_verts );
  Math_NS::Box3D box( const Shape& );
}