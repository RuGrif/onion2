#include "Graph.h"


Collision_NS::Node::Node( Node&& i_node )
  : d_alpha( std::move( i_node.d_alpha ) )
  , d_beta( std::move( i_node.d_beta ) )
{

}


Collision_NS::Node& Collision_NS::Node::operator = ( Node&& i_node )
{
  d_alpha = std::move( i_node.d_alpha );
  d_beta = std::move( i_node.d_beta );
  return *this;
}


Collision_NS::Node::Node( std::unique_ptr<Prim>&& a, std::unique_ptr<Prim>&& b )
  : d_alpha( std::move( a ) ), d_beta( std::move( b ) )
{

}


Collision_NS::Node::~Node()
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
