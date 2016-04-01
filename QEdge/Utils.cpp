#include "Utils.h"
#include <unordered_set>
#include <numeric>


namespace
{
  template <typename ID>
  std::vector<QEdge_NS::Edge> all( const QEdge_NS::Shape& i_shape, ID id )
  {
    std::vector<QEdge_NS::Edge> out;
    std::unordered_set<size_t> visited;

    for( QEdge_NS::Edge e : i_shape )
    {
      if( visited.insert( id( e ) ).second ) out.push_back( e );
      e = e.sym();
      if( visited.insert( id( e ) ).second ) out.push_back( e );
    }

    return out;
  }
}


std::vector<QEdge_NS::Edge> QEdge_NS::allVerts( const Shape& i_shape )
{
  return ::all( i_shape, []( Edge e ) { return e.o().id(); } );
}


std::vector<QEdge_NS::Edge> QEdge_NS::allFaces( const Shape& i_shape )
{
  return ::all( i_shape, []( Edge e ) { return e.l().id(); } );
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
