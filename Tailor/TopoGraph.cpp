#include "TopoGraph.h"
#include "checked_insert.h"


using Collision_NS::makeXPoint;
using Collision_NS::makeXPointID;


size_t Tailor_NS::Collection::size() const
{
  return
    get<Collision_NS::XVert, Collision_NS::XVert>().size() +
    get<Collision_NS::XVert, Collision_NS::XEdge>().size() +
    get<Collision_NS::XVert, Collision_NS::XFace>().size() +
    get<Collision_NS::XEdge, Collision_NS::XVert>().size() +
    get<Collision_NS::XEdge, Collision_NS::XEdge>().size() +
    get<Collision_NS::XEdge, Collision_NS::XFace>().size() +
    get<Collision_NS::XFace, Collision_NS::XVert>().size() +
    get<Collision_NS::XFace, Collision_NS::XEdge>().size();
}


void Tailor_NS::TopoGraph::add( const V& a, const V& b, bool alter ) { push( a, b, alter ); }
void Tailor_NS::TopoGraph::add( const V& a, const E& b, bool alter ) { push( a, b, alter ); }
void Tailor_NS::TopoGraph::add( const V& a, const F& b, bool alter ) { push( a, b, alter ); }
void Tailor_NS::TopoGraph::add( const E& a, const E& b, bool alter ) { push( a, b, alter ); }
void Tailor_NS::TopoGraph::add( const E& a, const F& b, bool alter ) { push( a, b, alter ); }


template <typename A, typename B>
void Tailor_NS::TopoGraph::push( const A& a, const B& b, bool alter )
{
  return alter ? push( b, a ) : push( a, b );
}


template <typename A, typename B>
void Tailor_NS::TopoGraph::push( const A& a, const B& b )
{
  auto i = collection().get<A, B>().emplace(
    std::piecewise_construct,
    std::forward_as_tuple( makeXPointID( a, b ) ),
    std::forward_as_tuple( a, b ) );

  if( !i.second ) throw DuplicatedMapEntry{};
}
