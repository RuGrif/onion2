#include "Graph.h"


void Collision_NS::Graph::push( std::unique_ptr<Node>&& i_node )
{
  d_verts[ i_node->id() ] = std::move( i_node );
}


Collision_NS::Graph::Nodes Collision_NS::Graph::all() const
{
  Nodes nodes;
  for( auto& node : d_verts ) nodes.push_back( std::cref( *node.second ) );
  return nodes;
}


Collision_NS::Graph::Nodes Collision_NS::Graph::neighborhood( const Node& i_node ) const
{
  Prim::Neighborhood alphaNb = i_node.alpha().neighbourhood();
  Prim::Neighborhood betaNb = i_node.beta().neighbourhood();

  Nodes nb;

  for( size_t alpha : alphaNb )
  {
    for( size_t beta : betaNb )
    {
      //  remove this node from neighbrhood
      if( alpha == i_node.alpha() && beta == i_node.beta() ) continue;

      auto f = d_verts.find( std::make_pair( alpha, beta ) );
      if( f != d_verts.end() ) nb.push_back( std::cref( *f->second ) );
    }
  }

  return nb;
}