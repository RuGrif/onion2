#include "Graph.h"


template <typename A, typename B>
Collision_NS::Node::Node( QEdge_NS::Edge a, QEdge_NS::Edge b )
  : d_alpha( std::make_unique<A>( a ) )
  , d_beta( std::make_unique<B>( b ) )
{

}


bool Collision_NS::operator == ( const Node& x, const Node& y )
{
  return x.alpha() == y.alpha() && x.beta() == y.beta();
}


std::size_t std::hash<Collision_NS::NodeId>::operator() ( const Collision_NS::NodeId& id ) const
{
  return id.first ^ id.second;
}


Collision_NS::Graph::Neighborhood Collision_NS::Graph::neighborhood( const Node& i_node ) const
{
  Neighborhood nb;

  for( size_t alpha : i_node.alpha().neighbourhood() )
  {
    for( size_t beta : i_node.beta().neighbourhood() )
    {
      //  remove this node from neighbrhood
      if( alpha == i_node.alpha() && beta == i_node.beta() ) continue;

      auto f = d_verts.find( std::make_pair( alpha, beta ) );
      if( f != d_verts.end() ) nb.push_back( std::ref( f->second ) );
    }
  }

  return nb;
}