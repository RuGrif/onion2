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

  auto stitch = []( QEdge_NS::Edge a, QEdge_NS::Edge b, const Math_NS::Vector3F& v )
  {
    if( a.oNext() != b ) a.splice0( b.oPrev() );
    if( !a.o() ) a.o().reset<Point3D>( v.x, v.y, v.z );
  };

  stitch( ea, ec.sym(), a );
  stitch( eb, ea.sym(), b );
  stitch( ec, eb.sym(), c );
}


QEdge_NS::Shape&& IO_NS::Constructor::getShape( Constructor&& c )
{
  return std::move( c.d_shape );
}

QEdge_NS::Edge IO_NS::Constructor::getOrConstructEdge( const Math_NS::Vector3F& a, const Math_NS::Vector3F& b )
{
  auto f = d_edges.find( std::make_pair( b, a ) );  //  look for exist e.sym
  
  if( f == d_edges.end() )  //  first call
  {
    QEdge_NS::Edge e = d_shape.makeEdge();
    d_edges[ std::make_pair( a, b ) ] = e;
    return e;
  }
  else                      //  second call
  {
    QEdge_NS::Edge e = f->second.sym();
    d_edges.erase( f );
    return e;
  }
}
