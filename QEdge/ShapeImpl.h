#pragma once


#include "Shape.h"
#include "Quad.h"
#include <list>


struct QEdge_NS::Shape::Impl
{
  std::list<Quad> d_quads;
  
  using Iterator = std::list<Quad>::iterator;
};