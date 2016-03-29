#pragma once


#include "../Collision/Intersection.h"
#include <map>


namespace Test_NS
{
  struct Intersection : public Collision_NS::Intersection
  {
    using V = Collision_NS::XVert;
    using E = Collision_NS::XEdge;
    using F = Collision_NS::XFace;

    virtual void add( const V& a, const V& b, bool alter ) { push( a, b, alter ); }
    virtual void add( const V& a, const E& b, bool alter ) { push( a, b, alter ); }
    virtual void add( const V& a, const F& b, bool alter ) { push( a, b, alter ); }
    virtual void add( const E& a, const E& b, bool alter ) { push( a, b, alter ); }
    virtual void add( const E& a, const F& b, bool alter ) { push( a, b, alter ); }

    template <typename A, typename B> void push( const A& a, const B& b, bool alter )
    {
      alter ? push( b, a ) : push( a, b );
    }

    template <typename A, typename B> void push( const A& a, const B& b )
    {
      d_xpoints[ makeXPointID( a, b ) ] = point( a, b );
    }

    std::map<Collision_NS::XPointID, Math_NS::Vector3D> d_xpoints;
  };
}