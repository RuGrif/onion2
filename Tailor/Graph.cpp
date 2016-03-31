#include "Graph.h"


using Collision_NS::makeXPoint;
using Collision_NS::makeXPointID;


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
  get<A, B>().emplace( std::piecewise_construct, std::forward_as_tuple( makeXPointID( a, b ) ), std::forward_as_tuple( a, b ) );
}
