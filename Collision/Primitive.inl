#pragma once


#include "Primitive.h"


template <typename Func>
void Collision_NS::Vert::forEachNb( Func func ) const
{
  func( Vert{ e() }, Vert{ e() } );
  
  QEdge_NS::Edge i = e();
  do
  {
    func( Edge{ i }, Edge{ i } );
    func( Edge{ i }, Vert{ i.sym() } );
    func( Face{ i }, Face{ i } );
    
    QEdge_NS::Edge j = i.lPrev();
    QEdge_NS::Edge k = i.lNext();

    while( ( j = j.lPrev() )!= k )
    {
      func( Face{ j }, Edge{ j } );
    }
  }
  while( ( i = i.oNext() ) != e() );
}


template <typename Func>
void Collision_NS::Edge::forEachNb( Func func ) const
{
  func( Edge{ e() }, Edge{ e() } );

  for( QEdge_NS::Edge i : { e(), e().sym() } )
  {
    QEdge_NS::Edge j = i;
    QEdge_NS::Edge k = i.lNext();

    while( ( j = j.lPrev ) != k )
    {
      func( Face{ j }, Edge{ j } );
      func( Face{ j }, Vert{ j } );
    }

    func( Edge{ i }, Vert{ i } );
    func( Face{ k }, Edge{ k } );
  }
}


template <typename Func>
void Collision_NS::Face::forEachNb( Func func ) const
{
  func( Face{ e() }, Face{ e() } );

  QEdge_NS::Edge i = e();
  do
  {
    func( Face{ i }, Edge{ i } );
    func( Face{ i }, Vert{ i } );
  }
  while( ( i = i.lPrev() ) != e() );
}