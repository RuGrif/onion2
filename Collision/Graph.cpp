#include "Graph.h"


void Collision_NS::Graph::operator()( std::unique_ptr<Intersection>&& i_node )
{
  const auto id = i_node->id();
  d_verts[ id ] = std::move( i_node );
}


Collision_NS::Graph::Nodes Collision_NS::Graph::all() const
{
  Nodes nodes;
  for( auto& node : d_verts ) nodes.push_back( std::cref( *node.second ) );
  return nodes;
}


Collision_NS::Graph::Nodes Collision_NS::Graph::neighborhood( const Intersection& i_node ) const
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