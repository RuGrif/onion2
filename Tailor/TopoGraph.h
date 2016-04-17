#pragma once


#include "../Collision/Intersection.h"
#include <map>


namespace Tailor_NS
{
  template <typename A, typename B>
  using XPointMap = std::map<Collision_NS::XPointID, Collision_NS::XPoint<A, B>>;


  template <typename A, typename B>
  using XEdge = std::pair<A, B>;


  template <typename A, typename B>
  auto makeXEdge( A a, B b ) { return std::make_pair( a, b ); }


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


  //  Intersection graph
  //
  //  forEachXPoint used to traverse all intersection points
  //  Callback have to have ( XPoint<A, B> ) interface
  //
  //  forEachXEdge used to traverse all intersection edges
  //  Callback have to have ( XPoint<A0, B0>, XEdge<EA, EB>, XPoint<A1, B1> ) interface
  class TopoGraph : public Collision_NS::Intersection
  {
  public:

    using V = Collision_NS::XVert;
    using E = Collision_NS::XEdge;
    using F = Collision_NS::XFace;

    const Collection& collection() const { return d_collection; }

    //  iterate all intersection points
    template <typename Func>
    void forEachXPoint( Func ) const;

    //  iterate all intersection points of type { A, B }
    template <typename A, typename B, typename Func>
    void forEachXPoint( Func ) const;

    //  iterate all intersection edges
    template <typename Func>
    void forEachXEdge( Func ) const;

    //  iterate all intersection edges starting from intersection point of type { A0, B0 }
    template <typename A0, typename B0, typename Func>
    void forEachXEdge( Func ) const;

    //  iterate all intersection edges starting from given intersection vertex
    template <typename A0, typename B0, typename Func>
    void forEachXEdge( const Collision_NS::XPoint<A0, B0>&, Func ) const;

  private:

    struct tagV { using type = V; };
    struct tagE { using type = E; };
    struct tagF { using type = F; };

    //  call func( A, B ) for each intersection vertex type X = { A::type, B::type }
    template <typename Func>
    static void forEachXPointType( Func );

  private:

    virtual void add( const V&, const V&, bool ) override;
    virtual void add( const V&, const E&, bool ) override;
    virtual void add( const V&, const F&, bool ) override;
    virtual void add( const E&, const E&, bool ) override;
    virtual void add( const E&, const F&, bool ) override;

  private:

    template <typename A, typename B> void push( const A&, const B&, bool );
    template <typename A, typename B> void push( const A&, const B& );

  private:

    Collection& collection() { return d_collection; }

  private:

    Collection  d_collection;
  };
}


#include "TopoGraph.inl"