#include "Shape.h"
#include "Quad.h"
#include <list>


struct QEdge_NS::Shape::Impl
{
  std::list<Quad> d_quads;
};


QEdge_NS::Shape::Shape() : impl( *new Impl ) {}
QEdge_NS::Shape::~Shape() { delete &impl; }


QEdge_NS::Edge QEdge_NS::Shape::makeEdge()
{
  impl.d_quads.emplace_back( Quad::Edge{} );
  return impl.d_quads.back().edge();
}


QEdge_NS::Edge QEdge_NS::Shape::makeLoop()
{
  impl.d_quads.emplace_back( Quad::Loop{} );
  return impl.d_quads.back().edge();
}
