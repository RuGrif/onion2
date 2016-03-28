#pragma once


#include "Intersection.h"
#include "../QEdge/Shape.h"
#include "Connection.h"
#include <map>
#include "Collision.h"


namespace Collision_NS
{
  struct XPointID //  for unit test purposes
  {
    virtual size_t alphaId() const = 0;
    virtual size_t betaId() const = 0;

  protected:

    ~XPointID() = default;
  };


  template <typename A, typename B>
  struct XPoint : public QEdge_NS::VertData, public XPointID
  {
    const A a;
    const B b;

    XPoint( const A& a, const B& b ) : a{ a }, b{ b } {}

    virtual const Math_NS::Vector3D point() const override { return Collision_NS::point( a, b ); }

    virtual size_t alphaId() const override { return id( a ); }
    virtual size_t betaId() const override { return id( b ); }
  };


  //  Intersection map
  class COLLISION_API Graph : public Intersection
  {
  public:

    const QEdge_NS::Shape& graph() const { return d_graph; }

  private:

    virtual void add( const XVert&, const XVert&, bool ) override;
    virtual void add( const XVert&, const XEdge&, bool ) override;
    virtual void add( const XVert&, const XFace&, bool ) override;
    virtual void add( const XEdge&, const XEdge&, bool ) override;
    virtual void add( const XEdge&, const XFace&, bool ) override;

  private:

    template <typename A, typename B> void makeXPoint( const A&, const B&, bool );
    template <typename A, typename B> void makeXPoint( const A&, const B& );
    void connect( const XVertID&, const YVertID& );

  private:

    #pragma warning( suppress : 4251 )
    Connection      d_xpoints;
    QEdge_NS::Shape d_graph;
  };
}