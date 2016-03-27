#pragma once


#include "Node.h"


template <typename Data> template <typename T, typename ... Args>
void QEdge_NS::Node<Data>::reset( Args&& ... args )
{
  d_data = std::make_unique<T>( std::forward<Args>( args )... );
}


template <typename Data>
void QEdge_NS::Node<Data>::swap( Node& other )
{
  d_data.swap( other.d_data );
}


template <typename Data>
QEdge_NS::Node<Data>::operator bool() const
{
  return static_cast<bool>( d_data );
}


template <typename Data>
const Data& QEdge_NS::Node<Data>::operator* ( ) const
{
  if( !d_data ) throw Null{ id() };
  return *d_data;
}


template <typename Data>
Data& QEdge_NS::Node<Data>::operator* ( )
{
  if( !d_data ) throw Null{ id() };
  return *d_data;
}


template <typename Data>
const Data* QEdge_NS::Node<Data>::operator-> ( ) const
{
  return &operator* ( );
}


template <typename Data>
Data* QEdge_NS::Node<Data>::operator-> ( )
{
  return &operator* ( );
}
