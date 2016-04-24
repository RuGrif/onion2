#pragma once


#include "TopoGraph.h"
#include "../QEdge/Shape.h"


namespace Tailor_NS
{
  TopoGraph intersect( QEdge_NS::Shape&, QEdge_NS::Shape& );

  void cut( QEdge_NS::Shape&, QEdge_NS::Shape&, const TopoGraph& );
  void cut( QEdge_NS::Shape&, QEdge_NS::Shape& );
}