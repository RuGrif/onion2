#pragma once


#include "Graph.h"


namespace Tailor_NS
{
  template <typename T> struct XType { using type = T; };

  template <> struct XType<Collision_NS::Vert> { using type = Collision_NS::XVert; };
  template <> struct XType<Collision_NS::Edge> { using type = Collision_NS::XEdge; };
  template <> struct XType<Collision_NS::Face> { using type = Collision_NS::XFace; };


  template <
    typename A0, typename B0,
    typename EA, typename EB,
    typename A1, typename B1,
    typename Func>
  void call(
    const Collection& c,
    const Collision_NS::XPoint<A0, B0>& p0,
    EA ea, EB eb,
    A1 a1, B1 b1,
    Func func )
  {
    if( Collision_NS::makeXPointID( a1, b1 ) != Collision_NS::makeXPointID( p0 ) )
    {
      if( auto p1 = c.xfind( a1, b1 ) )
      {
        func( p0, makeXEdge( ea, eb ), *p1 );
      }
    }
  }


  template <typename A0, typename B0, typename Func>
  void call(
    const Collection&,
    const Collision_NS::XPoint<A0, B0>&,
    Collision_NS::Face, Collision_NS::Face,
    Collision_NS::Face, Collision_NS::Face,
    Func )
  {
    //  intersection vertex can't have type { F, F }
  }
}


template <typename A, typename B>
auto Tailor_NS::Collection::xfind( A a, B b ) const
{
  auto& c = get<typename XType<A>::type, typename XType<B>::type>();

  auto i = c.find( makeXPointID( a, b ) );
  
  return ( i == c.end() ) ? nullptr : &i->second;
}


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
void Tailor_NS::Graph::forEachXPoint( Func func ) const
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
void Tailor_NS::Graph::forEachXPoint( Func func ) const
{
  for( const auto& i : collection().get<A, B>() )
  {
    func( i.second );
  }
}


//////////////////////////////////////////////////////////////////////////
//  XEdge -> XEdge<A0, B0> -> XEdge<A0, B0>( p0 ) -> XEdge<A0, B0, A1, B1>( p0 )


template <typename Func>
void Tailor_NS::Graph::forEachXEdge( Func func ) const
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
void Tailor_NS::Graph::forEachXEdge( Func func ) const
{
  //  for p0
  forEachXPoint<A0, B0>( [this, func]( const auto& p0 )
  {
    forEachXEdge( p0, func );
  } );
}


template <typename A0, typename B0, typename Func>
void Tailor_NS::Graph::forEachXEdge( const Collision_NS::XPoint<A0, B0>& p0, Func func ) const
{
  p0.first.forEachNb( [&]( auto ae, auto a1 )
  {
    p0.second.forEachNb( [&]( auto be, auto b1 )
    {
      call( collection(), p0, ae, be, a1, b1, func );
    } );
  } );
}