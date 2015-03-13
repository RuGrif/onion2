#include "Graph.h"


std::size_t std::hash<Collision_NS::Node>::operator() ( const N& n ) const
{
  return n.first->id() ^ n.second->id();
}


bool Collision_NS::operator == ( const Node& x, const Node& y )
{
  return *x.first == *y.first && *x.second == *y.second;
}


Collision_NS::Graph::Neighborhood Collision_NS::Graph::neighborhood( const Node& i_node ) const
{
  Neighborhood nb;

  for( std::unique_ptr<Prim>& alpha : i_node.first->neighbourhood() )
  {
    for( std::unique_ptr<Prim>& beta : i_node.second->neighbourhood() )
    {
      Node n;
      
      n.first.swap( alpha );
      n.second.swap( beta );
      
      auto i = d_verts.find( n );

      alpha.swap( n.first );
      beta.swap( n.second );
      
      if( i != d_verts.end() ) nb.push_back( std::make_pair( i->first->copy(), i->second->copy() ) );
    }
  }

  return nb;
}