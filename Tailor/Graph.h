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
    template <typename A, typename B> const XPointMap<A, B>& get() const { return *this; }
    template <typename A, typename B>       XPointMap<A, B>& get()       { return *this; }
  };


  class TAILOR_API Graph : public Collision_NS::Intersection
  {
  public:

    using V = Collision_NS::XVert;
    using E = Collision_NS::XEdge;
    using F = Collision_NS::XFace;

    const Collection& collection() const { return d_collection; }

    //  iterate all intersection points
    template <typename Func>
    void forEachXPoint( Func );

    //  iterate all intersection points of type { A, B }
    template <typename A, typename B, typename Func>
    void forEachXPoint( Func );

    //  iterate all intersection edges
    template <typename Func>
    void forEachXEdge( Func );

    //  iterate all intersection edges starting from intersection point of type { A0, B0 }
    template <typename A0, typename B0, typename Func>
    void forEachXEdge( Func );

    //  iterate all intersection edges starting from given intersection vertex
    template <typename A0, typename B0, typename Func>
    void forEachXEdge( const Collision_NS::XPoint<A0, B0>&, Func );

    //  iterate all intersection edges starting from given intersection vertex
    //  and ending on any intersection point of type X1 = { A1, B1 }
    template <typename A0, typename B0, typename A1, typename B1, typename Func>
    void forEachXEdge( const Collision_NS::XPoint<A0, B0>&, Func );

  private:

    struct tagV { using type = V; };
    struct tagE { using type = E; };
    struct tagF { using type = F; };

    //  call func( A, B ) for each intersection vertex type X = { A::type, B::type }
    template <typename Func>
    void forEachXPointType( Func );

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