#pragma once


#include "Loop.h"
#include <utility>


template <typename T>
QEdge_NS::Loop<T>::Loop( Dual& i_dual )
  : d_dual( i_dual )
  , d_edge( std::make_unique<Edge>() )
{
  
}


template<typename T>
auto QEdge_NS::Loop<T>::vert() -> Vert&
{
  if( !d_vert )
  {
    set( new Vert );
  }

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
    if( other.d_vert ) other.set( nullptr );
  }
  else
  {
    delete other.d_vert;
    other.set( d_vert );
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
    if( d_next->d_vert ) d_next->set( nullptr ); //  former other->next
  }
  else
  {
    delete other.d_vert;
    other.set( d_vert );
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
