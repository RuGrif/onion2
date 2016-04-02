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
  };


  struct Edge : public Prim
  {
    Edge( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    Vert                            U() const { return e(); }
    Vert                            V() const { return e().sym(); }

    //  the first edge in a quad is major and the second, the symmetrical, is minor
    bool                            isMajor() const { return e().id() < e().sym().id(); }
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
  };


  inline size_t id( Vert v ) { return v.e().o().id(); }
  inline size_t id( Edge e ) { return std::min( e.e().id(), e.e().sym().id() ); }
  inline size_t id( Face f ) { return f.e().l().id(); }


  std::vector<size_t> nb( Vert );
  std::vector<size_t> nb( Edge );
  std::vector<size_t> nb( Face );
}