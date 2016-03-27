#pragma once


#include "Shape.h"
#include <vector>
#include "QEdge.h"
#include "../Math/Box3.h"


namespace QEdge_NS
{
  QEDGE_API std::vector<Edge> allVerts( const Shape& );
  QEDGE_API std::vector<Edge> allEdges( const Shape& );
  QEDGE_API std::vector<Edge> allFaces( const Shape& );

  QEDGE_API Math_NS::Box3D box( const std::vector<Edge>& i_verts );
  QEDGE_API Math_NS::Box3D box( const Shape& );
}