#pragma once


#include "Node.h"
#include "QEdge.h"


namespace QEdge_NS
{
  template <typename T> class Loop;


  class QEDGE_API Edge
  {
  public:

    Edge() = default;
    Edge( const Edge& ) = default;
    Edge& operator = ( const Edge& ) = default;

    using Loop = Loop<Vert>;
    using Prim = Vert::Edge;
    using Dual = Prim::Dual;

    Edge( Loop& i_loop ) : d_loop( &i_loop ) {}

    operator bool() const { return d_loop != nullptr; }

    Edge oNext() const;
    Edge oPrev() const;
    Edge dNext() const;
    Edge dPrev() const;
    Edge lNext() const;
    Edge lPrev() const;
    Edge rNext() const;
    Edge rPrev() const;

    Edge sym() const; //  opposite edge

    Vert& o() const;  //  origin vertex
    Vert& d() const;  //  destination vertex
    Face& l() const;  //  left face
    Face& r() const;  //  right face
    Prim& n() const;  //  north (this) edge data
    Prim& s() const;  //  south (opposite) edge data
    Dual& e() const;  //  east (CW rotated) edge data
    Dual& w() const;  //  west (CCW rotated) edge data

    void splice0( Edge );   //  preserve this->o and this->l node data
    void splice1( Edge );   //  preserve this->o and edge->l node data

    size_t id() const { return reinterpret_cast<size_t>( d_loop ); }

  public:

    friend bool operator == ( Edge a, Edge b ) { return a.d_loop == b.d_loop; }
    friend bool operator != ( Edge a, Edge b ) { return a.d_loop != b.d_loop; }

  private:

    Loop* d_loop = nullptr;
  };
}