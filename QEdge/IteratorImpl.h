#pragma once


#include "Iterator.h"
#include "ShapeImpl.h"


struct QEdge_NS::Iterator::Impl
{
  Shape::Impl::Iterator d_iter;
};