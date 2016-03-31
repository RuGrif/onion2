#pragma once


#include "Graph.h"


template <typename A0, typename B0, typename A1, typename B1, typename Func>
void Tailor_NS::Graph::forEachXEdge( Func func )
{
  for( const auto& i0 : get<A0, B0>() )
  {
    forEachXEdge<A0, B0, A1, B1>( i0.second, func );
  }
}


template <typename A0, typename B0, typename A1, typename B1, typename Func>
void Tailor_NS::Graph::forEachXEdge( const Collision_NS::XPoint<A0, B0>& p0, Func func )
{
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


namespace Tailor_NS
{
  namespace ForEach_NS
  {
    using V = Graph::V;
    using E = Graph::E;
    using F = Graph::F;


    template <typename A0, typename B0, typename Func>
    void forEachX1Type( Func );


    template <typename Func>
    void forEachX0Type( Func f )
    {
      forEachX1Type<V, V>( f );
      forEachX1Type<V, E>( f );
      forEachX1Type<V, F>( f );

      forEachX1Type<E, V>( f );
      forEachX1Type<E, E>( f );
      forEachX1Type<E, F>( f );

      forEachX1Type<F, V>( f );
      forEachX1Type<F, E>( f );
    }


    template <typename A0, typename B0, typename Func>
    void forEachX1Type( Func f )
    {
      f.call<A0, B0, V, V>();
      f.call<A0, B0, V, E>();
      f.call<A0, B0, V, F>();

      f.call<A0, B0, E, V>();
      f.call<A0, B0, E, E>();
      f.call<A0, B0, E, F>();

      f.call<A0, B0, F, V>();
      f.call<A0, B0, F, E>();
    }


    template <typename Func>
    struct CallAll
    {
      Func    f;
      Graph&  g;

      template <typename A0, typename B0, typename A1, typename B1>
      void call()
      {
        g.forEachXEdge<A0, B0, A1, B1>( f );
      }
    };

    
    template <typename Func>
    CallAll<Func> makeCallAll( Func f, Graph& g ) { return CallAll<Func>{ f, g }; }


    template <typename A0, typename B0, typename Func>
    struct CallOne
    {
      using X = Collision_NS::XPoint<A0, B0>;

      Func      f;
      Graph&    g;
      const X&  p0;

      template <typename A0, typename B0, typename A1, typename B1>
      void call()
      {
        g.forEachXEdge<A0, B0, A1, B1>( p0, f );
      }
    };

    template <typename A0, typename B0, typename Func>
    CallOne<A0, B0, Func> makeCallOne( Func f, Graph& g, const Collision_NS::XPoint<A0, B0>& p0 ) { return CallOne<Func>{ f, g, p0 }; }
  }
}


template <typename Func>
void Tailor_NS::Graph::forEachXEdge( Func func )
{
  ForEach_NS::forEachX0Type( ForEach_NS::makeCallAll( func, *this ) );
}


template <typename A0, typename B0, typename Func>
void Tailor_NS::Graph::forEachXEdge( const Collision_NS::XPoint<A0, B0>& p0, Func func )
{
  ForEach_NS::forEachX0Type( ForEach_NS::makeCallOne( func, *this, p0 ) );
}