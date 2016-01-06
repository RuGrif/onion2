#pragma once


#include "Loop.h"
#include <utility>


template<typename T>
QEdge_NS::Loop<T>::Loop( Dual & i_dual ) : d_dual( i_dual ) {}


template<typename T>
QEdge_NS::Loop<T>::~Loop()
{
  delete d_vert;
  detach();
}


template<typename T>
auto QEdge_NS::Loop<T>::vert() -> Vert&
{
  if( !d_vert ) set( new Vert );
  return *d_vert;
}


//  ring = other
template <typename T>
void QEdge_NS::Loop<T>::fuse0( Loop& other )
{
  //  detach / attach
  if( d_vert == other.d_vert )
  {
    std::swap( d_next, other.d_next );
    other.detach();
  }
  else
  {
    other.attach( d_vert );
    std::swap( d_next, other.d_next );
  }
}


//  ring = other->next
template <typename T>
void QEdge_NS::Loop<T>::fuse1( Loop& other )
{
  //  detach / attach
  if( d_vert == other.d_vert )
  {
    std::swap( d_next, other.d_next );
    detach(); //  former other->next
  }
  else
  {
    other.attach( d_vert );
    std::swap( d_next, other.d_next );
  }
}


template <typename T>
void QEdge_NS::Loop<T>::splice0( Loop& other )
{
  next().dual().fuse1( other.next().dual() ); //  preserve this->next->dual->next->o ring who is simply this->l ring
  fuse0( other );
}


template <typename T>
void QEdge_NS::Loop<T>::splice1( Loop& other )
{
  other.next().dual().fuse1( next().dual() ); //  preserve other->next->dual->next->o ring who is simply other->l ring
  fuse0( other );
}


template<typename T>
void QEdge_NS::Loop<T>::attach( Vert* i_vert )
{
  delete d_vert;
  set( i_vert );
}


template<typename T>
void QEdge_NS::Loop<T>::detach()
{
  if( d_vert ) set( nullptr );
}


template <typename T>
void QEdge_NS::Loop<T>::set( Vert* i_vert )
{
  Loop* loop = this;
  do
  {
    loop->d_vert = i_vert;
    loop = loop->d_next;
  }
  while( loop != this );
}
