#pragma once


#include "../QEdge/Edge.h"
#include <vector>
#include <memory>


namespace Collision_NS
{
  class Prim
  {
  public:

    Prim( QEdge_NS::Edge i_edge ) : d_edge( i_edge ) {}

    QEdge_NS::Edge                  e() const { return d_edge; }
    
  private:

    QEdge_NS::Edge                  d_edge;
  };


  struct Vert : public Prim
  {
    Vert( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}
    const Math_NS::Vector3D         point() const { return e().o()->point(); }

    template <typename Func> void   forEachNb( Func ) const;

  };


  struct Edge : public Prim
  {
    Edge( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    Vert                            U() const { return e(); }
    Vert                            V() const { return e().sym(); }

    //  the first edge in a quad is major and the second, the symmetrical, is minor
    bool                            isMajor() const { return e().id() < e().sym().id(); }

    template <typename Func> void   forEachNb( Func ) const;
  };


  struct Face : public Prim
  {
    Face( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    Edge                            AB() const { return e(); }
    Edge                            BC() const { return e().lNext(); }
    Edge                            CA() const { return e().lPrev(); }

    Vert                            A() const { return e(); }
    Vert                            B() const { return e().lNext(); }
    Vert                            C() const { return e().lPrev(); }

    template <typename Func> void   forEachNb( Func ) const;
  };


  inline size_t id( Vert v ) { return v.e().o().id(); }
  inline size_t id( Edge e ) { return std::min( e.e().id(), e.e().sym().id() ); }
  inline size_t id( Face f ) { return f.e().l().id(); }


  template <typename A, typename B>
  std::enable_if_t<std::is_base_of<Prim, A>::value && std::is_base_of<Prim, B>::value, bool>
  operator < ( A a, B b ) { return id( a ) < id( b ); }


  template <typename A, typename B>
  std::enable_if_t<std::is_base_of<Prim, A>::value && std::is_base_of<Prim, B>::value, bool>
  operator == ( A a, B b ) { return id( a ) == id( b ); }


  std::vector<size_t> nb( Vert );
  std::vector<size_t> nb( Edge );
  std::vector<size_t> nb( Face );


  Vert major( Vert ); //  for all possible edges representin Vert, return the major one
  Edge major( Edge ); //  for all possible edges representin Edge, return the major one
  Face major( Face ); //  for all possible edges representin Face, return the major one
}


#include "Primitive.inl"