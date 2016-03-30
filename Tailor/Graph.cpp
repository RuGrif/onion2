#include "Graph.h"
#include "Data.h"


void Tailor_NS::Graph::add( const V& a, const V& b, bool alter ) { push( a, b, alter ); }
void Tailor_NS::Graph::add( const V& a, const E& b, bool alter ) { push( a, b, alter ); }
void Tailor_NS::Graph::add( const V& a, const F& b, bool alter ) { push( a, b, alter ); }
void Tailor_NS::Graph::add( const E& a, const E& b, bool alter ) { push( a, b, alter ); }
void Tailor_NS::Graph::add( const E& a, const F& b, bool alter ) { push( a, b, alter ); }


template <typename A, typename B>
void Tailor_NS::Graph::push( const A& a, const B& b, bool alter )
{
  return alter ? push( b, a ) : push( a, b );
}


template <typename A, typename B>
void Tailor_NS::Graph::push( const A& a, const B& b )
{
  XPointMap<A, B>& c = d_collection.get<A, B>();

  //  skip operation is point was already added
  auto xid = std::make_pair( id( a ), id( b ) );
  if( c.find( xid ) != c.end() ) return;

  //  find possible intersection edges for this intersection vertex
  xedge( a, b );
  
  //  insert this intersection vertex into collection
  d_collection.get<A, B>().emplace( xid, std::make_pair( a, b ) );
}


namespace Tailor_NS
{
  template <typename A, typename B>
  void splice( std::vector<QEdge_NS::Edge>& e, const A& a, const B& b )
  {
    for( size_t i = 0; i + 1 < e.size(); ++i ) e[ i ].splice0( e[ i + 1 ] );

    if( !e.empty() ) e.front().o().reset<XPointData<A, B>>( a, b );
  }
}


template <typename A, typename B>
void Tailor_NS::Graph::xedge( const A& a, const B& b )
{
  std::vector<QEdge_NS::Edge> ea;
  std::vector<QEdge_NS::Edge> eb;

  for_each_nb<V, V>( a, b, ea, eb );
  for_each_nb<V, E>( a, b, ea, eb );
  for_each_nb<V, F>( a, b, ea, eb );
  for_each_nb<E, V>( a, b, ea, eb );
  for_each_nb<E, E>( a, b, ea, eb );
  for_each_nb<E, F>( a, b, ea, eb );
  for_each_nb<F, V>( a, b, ea, eb );
  for_each_nb<F, E>( a, b, ea, eb );

  splice( ea, a, b );
  splice( eb, b, a );
}


template <typename A1, typename B1, typename A0, typename B0>
void Tailor_NS::Graph::for_each_nb( const A0& a0, const B0& b0, std::vector<QEdge_NS::Edge>& ea, std::vector<QEdge_NS::Edge>& eb )
{
  XPointMap<A1, B1>& c = d_collection.get<A1, B1>();

  for( size_t ia : nb( a0 ) ) for( size_t ib : nb( b0 ) )
  {
    auto i = c.find( std::make_pair( ia, ib ) );
    if( i == c.end() ) continue;

    const A1& a1 = i->second.first;
    const B1& b1 = i->second.second;

    ea.push_back( d_alpha.add( a0, a1 ) );
    eb.push_back( d_beta.add( b0, b1 ) );
  }
}