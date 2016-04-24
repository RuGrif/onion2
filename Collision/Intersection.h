#pragma once


#include "XPoint.h"
#include <set>


namespace Collision_NS
{
  //  Callback for Intersection Vertexes
  class Intersection
  {
  public:

    using Int = Math_NS::Vector3L::Type;

    void operator() ( const XVert&, const XVert&, bool );
    void operator() ( const XVert&, const XEdge&, bool );
    void operator() ( const XVert&, const XFace&, bool );
    void operator() ( const XEdge&, const XEdge&, bool );
    void operator() ( const XEdge&, const XFace&, bool );

    void markOverlap( const XSegmentID& );
    bool areOverlap( const XSegmentID& ) const;

    virtual ~Intersection() = default;

  private:

    virtual void add( const XVert&, const XVert&, bool ) = 0;
    virtual void add( const XVert&, const XEdge&, bool ) = 0;
    virtual void add( const XVert&, const XFace&, bool ) = 0;
    virtual void add( const XEdge&, const XEdge&, bool ) = 0;
    virtual void add( const XEdge&, const XFace&, bool ) = 0;

  private:

    std::set<XSegmentID> d_overlaps;
  };
}
