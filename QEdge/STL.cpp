#include "STL.h"
#include <fstream>
#include <unordered_map>


namespace QEdge_NS
{
  static_assert( sizeof( float ) == 4, "float size should be 4 bytes" );
  static_assert( sizeof( uint32_t ) == 4, "uint32_t size should be 4 bytes" );
  
  using Vector3F = Vector3<float>;
  
  static_assert( sizeof( QEdge_NS::Vector3F ) == 3 * 4, "Vector3F size should be 3 * 4 bytes" );
  static_assert( sizeof( QEdge_NS::Vector3F[3] ) == 3 * 3 * 4, "Vector3F[3] size should be 3 * 3 * 4 bytes" );


  class ShapeConstructor
  {
  public:

    void addTriangle( const Vector3F& a, const Vector3F& b, const Vector3F& c )
    {
      Edge ea = getOrConstructEdge( a, b );
      Edge eb = getOrConstructEdge( b, c );
      Edge ec = getOrConstructEdge( c, a );

      stitch( ea, ec.sym() );
      stitch( eb, ea.sym() );
      stitch( ec, eb.sym() );
    }

    Shape getShape()
    {
      assignVertexData();
      return std::move( d_shape );
    }

  private:

    void stitch( Edge a, Edge b )
    {
      if( a.oNext() != b ) a.splice0( b.oPrev() );
    }

    Edge getOrConstructEdge( const Vector3F& a, const Vector3F& b )
    {
      auto f = d_edges.find( std::make_pair( b, a ) );  //  look for exist e.sym
      return ( f == d_edges.end() ) ? ( d_edges[ std::make_pair( a, b ) ] = d_shape.makeEdge() ) : f->second.sym();
    }

    void assignVertexData()
    {
      for( auto i : d_edges )
      {
        Edge e = i.second;
        std::pair<Vector3F, Vector3F> p = i.first;

        makeVertex( e.o(), p.first );
        makeVertex( e.d(), p.second );
      }
    }

    void makeVertex( Vert& v, const Vector3F& p )
    {
      class Point3D : public VertData
      {
      public:

        Point3D( float x, float y, float z ) : d_point( static_cast<double>( x ), static_cast<double>( y ), static_cast<double>( z ) ) {}

        virtual Vector3D point() const override { return d_point; }
        virtual void point( const Vector3D& i_point ) override { d_point = i_point; }

      private:

        Vector3D d_point;
      };

      if( !v ) v.reset<Point3D>( p.x, p.y, p.z );
    }

  private:

    class Hash
    {
      static_assert( sizeof( size_t ) == sizeof( float ), "Hash expects size of size_t and float are equal" );

      static const size_t s = 8 * sizeof( float ) / 6;

      size_t h( float v, size_t shift ) const
      {
        return *reinterpret_cast<size_t*>( &v ) << shift * s;
      }

    public:

      //  hash
      size_t operator() ( const std::pair<Vector3F, Vector3F>& v ) const
      {
        return h( v.first.x, 0 ) ^ h( v.first.y, 2 ) ^ h( v.first.y, 4 ) ^ h( v.second.x, 1 ) ^ h( v.second.y, 3 ) ^ h( v.second.y, 5 );
      }
    };

  private:

    Shape d_shape;
    std::unordered_map<std::pair<Vector3F, Vector3F>, Edge, Hash> d_edges;
  };
}


QEdge_NS::Shape QEdge_NS::read( const std::wstring& i_fileName )
{
  ShapeConstructor constructor;

  //
  //  Read binary STL file
  //

  std::ifstream file( i_fileName, std::ifstream::binary );
  file.exceptions( file.badbit | file.failbit );

  file.seekg( 80 ); // header

  uint32_t nf = 0;
  file.read( reinterpret_cast<char*>( &nf ), 4 );

  for( uint32_t f = 0; f < nf; ++f )
  {
    Vector3F verts[ 3 ];

    static_assert( sizeof( verts ) == 3 * 3 * 4, "Invalid Vector3F[3] array size" );

    file.seekg( 3 * 4, std::ifstream::cur ); //  normal
    file.read( reinterpret_cast<char*>( verts ), 3 * 3 * 4 );
    file.seekg( 2, std::ifstream::cur );  //  attribute

    constructor.addTriangle( verts[ 0 ], verts[ 1 ], verts[ 2 ] );
  }

  return constructor.getShape();
}
