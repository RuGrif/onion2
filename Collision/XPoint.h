#pragma once


#include "Primitive.h"
#include "Barycentric.h"


namespace Collision_NS
{
  //
  //  Intersection primitive
  //


  struct XVert;
  struct XEdge;
  struct XFace;


  class BadUpcast;


  struct XVert : public Vert, public BaryV
  {
    XVert( Vert v ) : Vert{ v } {}

    XEdge toXEdge( Edge ) const;
    XFace toXFace( Face ) const;
  };


  struct XEdge : public Edge, public BaryE
  {
    XEdge( Edge e, Int u, Int v ) : Edge{ e }, BaryE{ u, v } {}

    XFace toXFace( Face ) const;
  };


  struct XFace : public Face, public BaryF
  {
    XFace( Face f, Int a, Int b, Int c ) : Face{ f }, BaryF{ a, b, c } {}

    XFace toXFace( Face ) const;
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
  struct XPoint : std::pair<A, B> { using std::pair<A, B>::pair; };

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


  template <typename A, typename B>
  bool operator < ( const XPoint<A, B>& l, const XPoint<A, B>& r ) { return makeXPointID( l ) < makeXPointID( r ); }

  template <typename A, typename B>
  bool operator == ( const XPoint<A, B>& l, const XPoint<A, B>& r ) { return makeXPointID( l ) == makeXPointID( r ); }


  //
  //  Intersection segment as a pair of two intersecting primitives
  //


  template <typename A, typename B>
  struct XSegment : std::pair<A, B> { using std::pair<A, B>::pair; };

  template <typename A, typename B>
  XSegment<A, B> makeXSegment( const A& a, const B& b ) { return std::make_pair( a, b ); }


  //
  //  Intersection segment id
  //


  using XSegmentID = std::pair<size_t, size_t>;

  inline XSegmentID makeXSegmentID( size_t a, size_t b ) { return std::make_pair( a, b ); }

  template <typename A, typename B>
  XSegmentID makeXSegmentID( const A& a, const B& b ) { return makeXSegmentID( id( a ), id( b ) ); }

  template <typename A, typename B>
  XSegmentID makeXSegmentID( const XSegment<A, B>& p ) { return makeXPointID( p.first, p.second ); }

  template <typename A, typename B>
  bool operator < ( const XSegment<A, B>& l, const XSegment<A, B>& r ) { return makeXSegmentID( l ) < makeXSegmentID( r ); }

  template <typename A, typename B>
  bool operator == ( const XSegment<A, B>& l, const XSegment<A, B>& r ) { return makeXSegmentID( l ) == makeXSegmentID( r ); }


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
