#include "Iterator.h"
#include "IteratorImpl.h"



QEdge_NS::Iterator::Iterator() : d_pimpl( std::make_shared<Impl>() ) {}
QEdge_NS::Iterator::~Iterator() {}


QEdge_NS::Iterator::Impl& QEdge_NS::Iterator::impl() const { return *d_pimpl; }


QEdge_NS::Iterator& QEdge_NS::Iterator::operator++ ( )
{
  ++impl().d_iter;
  return *this;
}


QEdge_NS::Iterator& QEdge_NS::Iterator::operator-- ( )
{
  --impl().d_iter;
  return *this;
}


QEdge_NS::Edge QEdge_NS::Iterator::operator* ( ) const
{
  return impl().d_iter->edge();
}


QEdge_NS::Edge QEdge_NS::Iterator::operator-> ( ) const
{
  return impl().d_iter->edge();
}


bool QEdge_NS::Iterator::operator == ( const Iterator& iter ) const
{
  return impl().d_iter == iter.impl().d_iter;
}


bool QEdge_NS::Iterator::operator != ( const Iterator& iter ) const
{
  return impl().d_iter != iter.impl().d_iter;
}

