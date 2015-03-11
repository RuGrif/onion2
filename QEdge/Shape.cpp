#include "Shape.h"
#include "ShapeImpl.h"
#include "IteratorImpl.h"


QEdge_NS::Shape::Shape() : d_pimpl( std::make_unique<Impl>() ) {}
QEdge_NS::Shape::~Shape() {}


QEdge_NS::Shape::Shape( Shape&& shape ) : Shape()
{
  d_pimpl.swap( shape.d_pimpl );
}


QEdge_NS::Shape& QEdge_NS::Shape::operator= ( Shape&& shape )
{
  d_pimpl.swap( shape.d_pimpl );
  return *this;
}


QEdge_NS::Shape::Impl& QEdge_NS::Shape::impl() const { return *d_pimpl; }


QEdge_NS::Edge QEdge_NS::Shape::makeEdge()
{
  impl().d_quads.emplace_back( Quad::Edge{} );
  return impl().d_quads.back().edge();
}


QEdge_NS::Edge QEdge_NS::Shape::makeLoop()
{
  impl().d_quads.emplace_back( Quad::Loop{} );
  return impl().d_quads.back().edge();
}


QEdge_NS::Iterator QEdge_NS::Shape::begin()
{
  Iterator iter;
  iter.impl().d_iter = impl().d_quads.begin();
  return iter;
}


QEdge_NS::Iterator QEdge_NS::Shape::end()
{
  Iterator iter;
  iter.impl().d_iter = impl().d_quads.end();
  return iter;
}


size_t QEdge_NS::Shape::size() const
{
  return d_pimpl->d_quads.size();
}