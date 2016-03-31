#pragma once


#include "../Collision/Intersection.h"
#include <map>
#include "Tailor.h"


namespace Tailor_NS
{
  template <typename A, typename B>
  using XPointMap = std::map<Collision_NS::XPointID, Collision_NS::XPoint<A, B>>;


  //  set of intersection points
  struct Collection
    : private XPointMap<Collision_NS::XVert, Collision_NS::XVert>
    , private XPointMap<Collision_NS::XVert, Collision_NS::XEdge>
    , private XPointMap<Collision_NS::XVert, Collision_NS::XFace>
    , private XPointMap<Collision_NS::XEdge, Collision_NS::XVert>
    , private XPointMap<Collision_NS::XEdge, Collision_NS::XEdge>
    , private XPointMap<Collision_NS::XEdge, Collision_NS::XFace>
    , private XPointMap<Collision_NS::XFace, Collision_NS::XVert>
    , private XPointMap<Collision_NS::XFace, Collision_NS::XEdge>
  {
    template <typename A, typename B> XPointMap<A, B>& get() { return *this; }
  };


  class TAILOR_API Graph : public Collision_NS::Intersection
  {
  public:

    using V = Collision_NS::XVert;
    using E = Collision_NS::XEdge;
    using F = Collision_NS::XFace;

    template <typename Func>
    void forEachXEdge( Func );

    template <typename A0, typename B0, typename A1, typename B1, typename Func>
    void forEachXEdge( Func );

  private:

    virtual void add( const V&, const V&, bool ) override;
    virtual void add( const V&, const E&, bool ) override;
    virtual void add( const V&, const F&, bool ) override;
    virtual void add( const E&, const E&, bool ) override;
    virtual void add( const E&, const F&, bool ) override;

  private:

    template <typename A, typename B> void push( const A&, const B&, bool );
    template <typename A, typename B> void push( const A&, const B& );

    template <typename A, typename B> XPointMap<A, B>& get() { return d_collection.get<A, B>(); }

  private:

    #pragma warning( suppress : 4251 )
    Collection  d_collection;
  };
}


#include "Graph.inl"