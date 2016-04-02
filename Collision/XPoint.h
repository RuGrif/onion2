#pragma once


#include "Primitive.h"


namespace Collision_NS
{
  //
  //  Intersection primitive
  //


  struct XVert;
  struct XEdge;
  struct XFace;


  class BadUpcast;


  struct XVert : public Vert
  {
    XVert( Vert v ) : Vert{ v } {}

    XEdge toXEdge( Edge );
    XFace toXFace( Face );
  };


  struct XEdge : public Edge
  {
    using Int = Math_NS::Vector3L::Type;

    const Int u;
    const Int v;

    XEdge( Edge e, Int u, Int v ) : Edge{ e }, u{ u }, v{ v } {}

    XFace toXFace( Face );
  };


  struct XFace : public Face
  {
    using Int = Math_NS::Vector3L::Type;

    const Int a;
    const Int b;
    const Int c;

    XFace( Face f, Int a, Int b, Int c ) : Face{ f }, a{ a }, b{ b }, c{ c } {}
  };


  class BadUpcast : public std::exception
  {
  public:

    BadUpcast( const size_t i_from, const size_t i_to ) : d_from{ i_from }, d_to{ i_to } {}

    virtual const char* what() const override { return "Upcast intersection primitive X to unrelated primitive Y"; }
    const size_t        from() const          { return d_from; }
    const size_t        to()   const          { return d_to; }

  private:

    const size_t d_from;
    const size_t d_to;
  };


  const Math_NS::Vector3D point( const XVert& );
  const Math_NS::Vector3D point( const XEdge& );


  //
  //  Intersection point as a pair of two intersecting primitives
  //


  template <typename A, typename B>
  using XPoint = std::pair<A, B>;

  template <typename A, typename B>
  XPoint<A, B> makeXPoint( const A& a, const B& b ) { return std::make_pair( a, b ); }


  //
  //  Intersection point id
  //


  using XPointID = std::pair<size_t, size_t>;

  inline XPointID makeXPointID( size_t a, size_t b ) { return std::make_pair( a, b ); }

  template <typename A, typename B>
  XPointID makeXPointID( const A& a, const B& b ) { return makeXPointID( id( a ), id( b ) ); }

  template <typename A, typename B>
  XPointID makeXPointID( const XPoint<A, B>& p ) { return makeXPointID( p.first, p.second ); }


  //
  //  Intersection point coordinates in global space
  //


  Math_NS::Vector3D point( const XVert&, const XVert& );
  Math_NS::Vector3D point( const XVert&, const XEdge& );
  Math_NS::Vector3D point( const XVert&, const XFace& );
  Math_NS::Vector3D point( const XEdge&, const XVert& );
  Math_NS::Vector3D point( const XEdge&, const XEdge& );
  Math_NS::Vector3D point( const XEdge&, const XFace& );
  Math_NS::Vector3D point( const XFace&, const XVert& );
  Math_NS::Vector3D point( const XFace&, const XEdge& );


  template <typename A, typename B>
  Math_NS::Vector3D point( const XPoint<A, B>& p ) { return point( p.first, p.second ); }
}
