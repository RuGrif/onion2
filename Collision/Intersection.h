#pragma once


#include "Primitive.h"
#include "Collision.h"


namespace Collision_NS
{
  struct XVert : public Vert
  {
    XVert( Vert v ) : Vert{ v } {}
  };


  struct XEdge : public Edge
  {
    using Int = Math_NS::Vector3L::Type;

    const Int u;
    const Int v;

    XEdge( Edge e, Int u, Int v ) : Edge{ e }, u{ u }, v{ v } {}
  };


  struct XFace : public Face
  {
    using Int = Math_NS::Vector3L::Type;

    const Int a;
    const Int b;
    const Int c;

    XFace( Face f, Int a, Int b, Int c ) : Face{ f }, a{ a }, b{ b }, c{ c } {}
  };


  const Math_NS::Vector3D point( const XVert& );
  const Math_NS::Vector3D point( const XEdge& );


  class COLLISION_API Intersection
  {
  public:

    using Int = Math_NS::Vector3L::Type;

    void operator() ( const XVert&, const XVert&, bool );
    void operator() ( const XVert&, const XEdge&, bool );
    void operator() ( const XVert&, const XFace&, bool );
    void operator() ( const XEdge&, const XEdge&, bool );
    void operator() ( const XEdge&, const XFace&, bool );

    virtual ~Intersection() = default;

  private:

    virtual void add( const XVert&, const XVert&, bool ) = 0;
    virtual void add( const XVert&, const XEdge&, bool ) = 0;
    virtual void add( const XVert&, const XFace&, bool ) = 0;
    virtual void add( const XEdge&, const XEdge&, bool ) = 0;
    virtual void add( const XEdge&, const XFace&, bool ) = 0;
  };


  const Math_NS::Vector3D point( const XVert&, const XVert& );
  const Math_NS::Vector3D point( const XVert&, const XEdge& );
  const Math_NS::Vector3D point( const XVert&, const XFace& );
  const Math_NS::Vector3D point( const XEdge&, const XVert& );
  const Math_NS::Vector3D point( const XEdge&, const XEdge& );
  const Math_NS::Vector3D point( const XEdge&, const XFace& );
  const Math_NS::Vector3D point( const XFace&, const XVert& );
  const Math_NS::Vector3D point( const XFace&, const XEdge& );
}
