#include "Constructor.h"


namespace
{
  class Point3D : public QEdge_NS::VertData
  {
  public:

    Point3D( float x, float y, float z ) : d_point( static_cast<double>( x ), static_cast<double>( y ), static_cast<double>( z ) )
    {

    }

    virtual Math_NS::Vector3D point() const override
    {
      return d_point;
    }

  private:

    Math_NS::Vector3D d_point;
  };
}


void IO_NS::Constructor::addTriangle( const Math_NS::Vector3F& a, const Math_NS::Vector3F& b, const Math_NS::Vector3F& c )
{
  QEdge_NS::Edge ea = getOrConstructEdge( a, b );
  QEdge_NS::Edge eb = getOrConstructEdge( b, c );
  QEdge_NS::Edge ec = getOrConstructEdge( c, a );

  auto stitch = []( QEdge_NS::Edge a, QEdge_NS::Edge b ) { if( a.oNext() != b ) a.splice0( b.oPrev() ); };

  stitch( ea, ec.sym() );
  stitch( eb, ea.sym() );
  stitch( ec, eb.sym() );
}


QEdge_NS::Shape&& IO_NS::Constructor::getShape( Constructor&& c )
{
  auto makeVertex = []( QEdge_NS::Vert& v, const Math_NS::Vector3F& p ) { if( !v ) v.reset<Point3D>( p.x, p.y, p.z ); };

  for( const auto& e : c.d_edges )
  {
    makeVertex( e.second.o(), e.first.first );
    makeVertex( e.second.d(), e.first.second );
  }

  return std::move( c.d_shape );
}

QEdge_NS::Edge IO_NS::Constructor::getOrConstructEdge( const Math_NS::Vector3F& a, const Math_NS::Vector3F& b )
{
  auto f = d_edges.find( std::make_pair( b, a ) );  //  look for exist e.sym
  return ( f == d_edges.end() ) ? ( d_edges[ std::make_pair( a, b ) ] = d_shape.makeEdge() ) : f->second.sym();
}