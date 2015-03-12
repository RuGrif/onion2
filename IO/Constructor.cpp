#include "Constructor.h"


namespace IO_NS
{
  class Point3D : public QEdge_NS::VertData
  {
  public:

    Point3D( float x, float y, float z ) : d_point( static_cast<double>( x ), static_cast<double>( y ), static_cast<double>( z ) ) {}

    virtual Math_NS::Vector3D point() const override { return d_point; }
    virtual void point( const Math_NS::Vector3D& i_point ) override { d_point = i_point; }

  private:

    Math_NS::Vector3D d_point;
  };
}


IO_NS::Constructor::Constructor( QEdge_NS::Shape& i_shape ) : d_shape( i_shape ) {}


void IO_NS::Constructor::addTriangle( const Math_NS::Vector3F& a, const Math_NS::Vector3F& b, const Math_NS::Vector3F& c )
{
  QEdge_NS::Edge ea = getOrConstructEdge( a, b );
  QEdge_NS::Edge eb = getOrConstructEdge( b, c );
  QEdge_NS::Edge ec = getOrConstructEdge( c, a );

  QEdge_NS::Vert ead, ebd, ecd;
  
  ea.d().swap( ead );
  eb.d().swap( ebd );
  ec.d().swap( ecd );

  stitch( ea, ec.sym() );
  stitch( eb, ea.sym() );
  stitch( ec, eb.sym() );

  ea.d().swap( ead );
  eb.d().swap( ebd );
  ec.d().swap( ecd );

  makeVertex( ea.o(), a );
  makeVertex( eb.o(), b );
  makeVertex( ec.o(), c );
}


QEdge_NS::Edge IO_NS::Constructor::getOrConstructEdge( const Math_NS::Vector3F& a, const Math_NS::Vector3F& b )
{
  auto f = d_edges.find( std::make_pair( b, a ) );  //  look for exist e.sym
  return ( f == d_edges.end() ) ? ( d_edges[ std::make_pair( a, b ) ] = d_shape.makeEdge() ) : f->second.sym();
}


void IO_NS::Constructor::stitch( QEdge_NS::Edge a, QEdge_NS::Edge b )
{
  if( a.oNext() != b ) a.splice0( b.oPrev() );
}


void IO_NS::Constructor::makeVertex( QEdge_NS::Vert& v, const Math_NS::Vector3F& p )
{
  if( !v ) v.reset<IO_NS::Point3D>( p.x, p.y, p.z );
}