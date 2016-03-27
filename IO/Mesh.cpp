#include "Mesh.h"
#include <fstream>
#include <unordered_map>


namespace IO_NS
{
  namespace
  {
    using Vec = Math_NS::Vector3D;

    struct Vertex
    {
      Vec d_Position;
      int d_Label;
    };

    struct Face
    {
      int d_V[ 3 ];
      int d_Label;
    };

    struct Edge
    {
      int d_V[ 2 ];
      int d_Label;
    };
  }
}


/*
The format is organized as follows:

V = number of vertices (32 bit unsigned integer)
Vertex #0
...
Vertex #(V-1)
F = number of faces (32 bit unsigned integer)
Face #0
...
Face #(F-1)
E = number of edges (32 bit unsigned integer)
Edge #0
...
Edge #(E-1)

Edges are optional.
*/


void IO_NS::writeMesh( const Collision_NS::Graph& i_graph, const std::wstring& i_fileName )
{
  std::unordered_map<Collision_NS::Intersection::ID, int> ids;

  std::ofstream file( i_fileName, std::ofstream::binary );
  file.exceptions( file.badbit | file.failbit );

  int label = 1;
  uint32_t size = 0;

  //  Verts
  auto verts = i_graph.all();

  size = verts.size();
  file.write( reinterpret_cast<char*>( &size ), sizeof( size ) );

  for( const Collision_NS::Intersection& node : verts )
  {
    Vertex v{ node.intersection(), label };
    file.write( reinterpret_cast<char*>( &v ), sizeof( v ) );
    ids.emplace( node.id(), ids.size() );
  }

  //  Faces
  size = 0;
  file.write( reinterpret_cast<char*>( &size ), sizeof( size ) );

  //  Edges
  size = 0;
  file.write( reinterpret_cast<char*>( &size ), sizeof( size ) );

  for( const Collision_NS::Intersection& node : verts )
  {
    for( const Collision_NS::Intersection& nb : i_graph.neighborhood( node ) )
    {
      Edge e{ ids.at( node.id() ), ids.at( nb.id() ), label };
      file.write( reinterpret_cast<char*>( &e ), sizeof( e ) );
      ++size;
    }
  }

  //  go back and write edge number
  file.seekp( -static_cast<std::ofstream::off_type>( size * sizeof( Edge ) + sizeof( size ) ), file.cur );
  file.write( reinterpret_cast<char*>( &size ), sizeof( size ) );
}