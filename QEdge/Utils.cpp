#include "Utils.h"
#include <unordered_set>
#include <numeric>


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


std::vector<QEdge_NS::Edge> QEdge_NS::allEdges( const Shape& i_shape )
{
  return{ i_shape.begin(), i_shape.end() };
}


Math_NS::Box3D QEdge_NS::box( const std::vector<Edge>& i_verts )
{
  Math_NS::Box3D b;
  for( Edge e : i_verts ) b += e.o()->point();
  return b;
}


Math_NS::Box3D QEdge_NS::box( const Shape& i_shape )
{
  return box( allVerts( i_shape ) );
}
