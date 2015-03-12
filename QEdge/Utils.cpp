#include "Utils.h"
#include <unordered_set>


std::vector<QEdge_NS::Edge> QEdge_NS::allVerts( const Shape& i_shape )
{
  std::vector<Edge> out;
  std::unordered_set<Vert*> visited;

  for( Edge e : i_shape )
  {
    if( visited.insert( &e.o() ).second ) out.push_back( e );
    e = e.sym();
    if( visited.insert( &e.o() ).second ) out.push_back( e );
  }

  return out;
}


std::vector<QEdge_NS::Edge> QEdge_NS::allFaces( const Shape& i_shape )
{
  std::vector<Edge> out;
  std::unordered_set<Face*> visited;

  for( Edge e : i_shape )
  {
    if( visited.insert( &e.l() ).second ) out.push_back( e );
    e = e.sym();
    if( visited.insert( &e.l() ).second ) out.push_back( e );
  }

  return out;
}
