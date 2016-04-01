#pragma once


#include "Graph.h"


template <typename Func>
void Tailor_NS::Graph::forEachXPointType( Func func )
{
  tagV v;
  tagE e;
  tagF f;

  func( v, v );
  func( v, e );
  func( v, f );

  func( e, v );
  func( e, e );
  func( e, f );

  func( f, v );
  func( f, e );
}


//////////////////////////////////////////////////////////////////////////
//  XPoint -> XPoint<A, B>


template <typename Func>
void Tailor_NS::Graph::forEachXPoint( Func func )
{
  //  for A, B
  forEachXPointType( [this, func]( auto a, auto b )
  {
    using A = decltype( a )::type;
    using B = decltype( b )::type;

    forEachXPoint<A, B>( func );
  } );
}


template <typename A, typename B, typename Func>
void Tailor_NS::Graph::forEachXPoint( Func func )
{
  for( const auto& i : get<A, B>() )
  {
    func( i.second );
  }
}


//////////////////////////////////////////////////////////////////////////
//  XEdge -> XEdge<A0, B0> -> XEdge<A0, B0>( p0 ) -> XEdge<A0, B0, A1, B1>( p0 )


template <typename Func>
void Tailor_NS::Graph::forEachXEdge( Func func )
{
  //  for A0, B0
  forEachXPointType( [this, func]( auto a0, auto b0 )
  {
    using A0 = decltype( a0 )::type;
    using B0 = decltype( b0 )::type;

    forEachXEdge<A0, B0>( func );
  } );
}


template <typename A0, typename B0, typename Func>
void Tailor_NS::Graph::forEachXEdge( Func func )
{
  //  for p0
  for( const auto& i0 : get<A0, B0>() )
  {
    forEachXEdge( i0.second, func );
  }
}


template <typename A0, typename B0, typename Func>
void Tailor_NS::Graph::forEachXEdge( const Collision_NS::XPoint<A0, B0>& p0, Func func )
{
  //  for A1, B1
  forEachXPointType( [this, func, &p0]( auto a1, auto b1 )
  {
    using A1 = decltype( a1 )::type;
    using B1 = decltype( b1 )::type;

    forEachXEdge<A0, B0, A1, B1>( p0, func );
  } );
}


template <typename A0, typename B0, typename A1, typename B1, typename Func>
void Tailor_NS::Graph::forEachXEdge( const Collision_NS::XPoint<A0, B0>& p0, Func func )
{
  auto nbA = nb( p0.first );
  auto nbB = nb( p0.second );

  //  for p1
  for( size_t ia : nbA ) for( size_t ib : nbB )
  {
    auto xid = Collision_NS::makeXPointID( ia, ib );

    auto i = get<A1, B1>().find( xid );
    if( i == get<A1, B1>().end() ) continue;

    const auto& p1 = i->second;

    func( p0, p1 );
  }
}