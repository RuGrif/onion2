#pragma once


#include "Primitive.h"


template <typename Func>
void Collision_NS::Vert::forEachNb( Func func ) const
{
  func( *this, *this );
  
  QEdge_NS::Edge i = e();
  do
  {
    func( Edge{ i }, Edge{ i } );
    func( Edge{ i }, Vert{ i.sym() } );
    func( Face{ i }, Face{ i } );
    func( Face{ i }, Edge{ i.lNext() } );
  }
  while( ( i = i.oNext() ) != e() );
}


template <typename Func>
void Collision_NS::Edge::forEachNb( Func func ) const
{
  func( *this, *this );

  for( QEdge_NS::Edge i : { e(), e().sym() } )
  {
    func( Face{ i }, Face{ i } );
    func( Edge{ i }, Vert{ i } );
    func( Face{ i }, Edge{ i.lPrev() } );
    func( Face{ i }, Edge{ i.lNext() } );
    func( Face{ i }, Vert{ i.lPrev() } );
  }
}


template <typename Func>
void Collision_NS::Face::forEachNb( Func func ) const
{
  func( *this, *this );

  func( *this, AB() );
  func( *this, BC() );
  func( *this, CA() );

  func( *this, A() );
  func( *this, B() );
  func( *this, C() );
}