#include "Mesh.h"
#include "../QEdge/Utils.h"
#include <fstream>
#include <map>
#include <cinttypes>


namespace IO_NS
{
  namespace
  {
    using Vec = Math_NS::Vector3D;

    struct Vertex
    {
      Vec       d_Position;
      uint32_t  d_Label;
    };

    struct Face
    {
      uint32_t  d_V[ 3 ];
      uint32_t  d_Label;
    };

    struct Edge
    {
      uint32_t  d_V[ 2 ];
      uint32_t  d_Label;
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

size_t makeLabel()
{
  static size_t s_label = 0;
  return ++s_label;
}


void IO_NS::writeMesh( const QEdge_NS::Shape& i_shape, const std::wstring& i_fileName )
{
  std::map<size_t, size_t> vid;
  std::ofstream file( i_fileName, std::ofstream::binary );
  file.exceptions( file.badbit | file.failbit );

  uint32_t label = makeLabel();
  uint32_t size = 0;

  //  Verts
  auto verts = allVerts( i_shape );

  size = verts.size();
  file.write( reinterpret_cast<char*>( &size ), sizeof( size ) );

  for( size_t i = 0; i < verts.size(); ++i )
  {
    Vertex v{ verts[ i ].o()->point(), label };
    file.write( reinterpret_cast<char*>( &v ), sizeof( v ) );
    vid[ verts[ i ].o().id() ] = i;
  }

  //  Faces
  size = 0;
  file.write( reinterpret_cast<char*>( &size ), sizeof( size ) );

  //  Edges
  auto edges = allEdges( i_shape );
  
  size = edges.size();
  file.write( reinterpret_cast<char*>( &size ), sizeof( size ) );

  for( QEdge_NS::Edge i : edges )
  {
    Edge e{ vid.at( i.o().id() ), vid.at( i.d().id() ), label };
    file.write( reinterpret_cast<char*>( &e ), sizeof( e ) );
  }
}