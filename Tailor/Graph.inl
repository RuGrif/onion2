#pragma once


#include "Graph.h"


namespace Tailor_NS
{
  template <typename T> struct XType;

  template <> struct XType<Collision_NS::Vert> { using type = Collision_NS::XVert; };
  template <> struct XType<Collision_NS::Edge> { using type = Collision_NS::XEdge; };
  template <> struct XType<Collision_NS::Face> { using type = Collision_NS::XFace; };


  namespace Graph_NS
  {
    template <typename A, typename B>
    using IsPossibleXPointType = std::conditional_t<
      std::is_same<A, Collision_NS::Face>::value &&
      std::is_same<B, Collision_NS::Face>::value
      , std::false_type
      , std::true_type>;


    template <typename A0, typename B0, typename EA, typename EB, typename A1, typename B1, typename Func>
    std::enable_if_t< IsPossibleXPointType<A1, B1>::value >
    call( const Collection& c, const Collision_NS::XPoint<A0, B0>& p0, EA ea, EB eb, A1 a1, B1 b1, Func func )
    {
      Collision_NS::XPointID xid = Collision_NS::makeXPointID( a1, b1 );
      if( xid == Collision_NS::makeXPointID( p0 ) ) return;

      auto& map = c.get<typename XType<A1>::type, typename XType<B1>::type>();

      auto i = map.find( xid );
      if( i == map.end() ) return;

      func( p0, makeXEdge( ea, eb ), i->second );
    }


    template <typename A0, typename B0, typename EA, typename EB, typename A1, typename B1, typename Func>
    std::enable_if_t< !IsPossibleXPointType<A1, B1>::value >
    call( const Collection&, const Collision_NS::XPoint<A0, B0>&, EA, EB, A1, B1, Func )
    {
      //  empty
    }
  }
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
      Graph_NS::call( collection(), p0, ae, be, a1, b1, func );
    } );
  } );
}