#pragma once


#include "Graph.h"


template <typename A0, typename B0, typename A1, typename B1, typename Func>
void Tailor_NS::Graph::forEachXEdge( Func func )
{
  for( const auto& i0 : get<A0, B0>() )
  {
    const auto& p0 = i0.second;

    auto nbA = nb( p0.first );
    auto nbB = nb( p0.second );

    for( size_t ia : nbA ) for( size_t ib : nbB )
    {
      auto xid = Collision_NS::makeXPointID( ia, ib );
      
      auto i = get<A1, B1>().find( xid );
      if( i == get<A1, B1>().end() ) continue;

      const auto& p1 = i->second;

      func( p0, p1 );
    }
  }
}


namespace Tailor_NS
{
  namespace ForEach_NS
  {
    using V = Graph::V;
    using E = Graph::E;
    using F = Graph::F;


    template <typename A0, typename B0, typename Func>
    void forEachX1Type( Func, Graph& );


    template <typename Func>
    void forEachX0Type( Func f, Graph& g )
    {
      forEachX1Type<V, V>( f, g );
      forEachX1Type<V, E>( f, g );
      forEachX1Type<V, F>( f, g );

      forEachX1Type<E, V>( f, g );
      forEachX1Type<E, E>( f, g );
      forEachX1Type<E, F>( f, g );

      forEachX1Type<F, V>( f, g );
      forEachX1Type<F, E>( f, g );
    }


    template <typename A0, typename B0, typename Func>
    void forEachX1Type( Func f, Graph& g )
    {
      g.forEachXEdge<A0, B0, V, V>( f );
      g.forEachXEdge<A0, B0, V, E>( f );
      g.forEachXEdge<A0, B0, V, F>( f );

      g.forEachXEdge<A0, B0, E, V>( f );
      g.forEachXEdge<A0, B0, E, E>( f );
      g.forEachXEdge<A0, B0, E, F>( f );

      g.forEachXEdge<A0, B0, F, V>( f );
      g.forEachXEdge<A0, B0, F, E>( f );
    }
  }
}


template <typename Func>
void Tailor_NS::Graph::forEachXEdge( Func func )
{
  Tailor_NS::ForEach_NS::forEachX0Type( func, *this );
}