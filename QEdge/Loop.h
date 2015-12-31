#pragma once


#include <memory>


namespace QEdge_NS
{
  //  represent an edge in quad-edge structure
  template <typename T>
  class Loop
  {
  public:

    using Vert = T;
    using Face = typename Vert::Dual;
    using Edge = typename Vert::Edge;
    using Dual = Loop<Face>;

    Loop( Dual& );

    const Loop& next() const { return *d_next; }
    Loop&       next()       { return *d_next; }

    const Dual& dual() const { return d_dual; }
    Dual&       dual()       { return d_dual; }

    const Vert& vert() const { return *d_vert; }
    Vert&       vert()       { return *d_vert; }

    const Edge& edge() const { return *d_edge; }
    Edge&       edge()       { return *d_edge; }

    void        fuse0( Loop& ); //  swap links and preserve this->o ring
    void        fuse1( Loop& ); //  swap links and preserve this->next->o ring

    void        splice0( Loop& ); //  preserve this->o and this->l rings
    void        splice1( Loop& ); //  preserve this->o and other->l rings

  private:

    //  update an this->o ring core
    void        reset( const std::shared_ptr<Vert>& );

  private:

    Loop*                           d_next = this; //  non-null pointer on next edge in a loop
    Dual&                           d_dual; //  non-null pointer on co-edge based on face nodes
    std::shared_ptr<Vert>           d_vert; //  non-null pointer on common vertex for this edge loop
    std::unique_ptr<Edge>           d_edge; //  non-null pointer on edge data for this concrete edge

  private:

    Loop() = delete;
    Loop( const Loop& ) = delete;
    Loop& operator = ( const Loop& ) = delete;
  };
}


#include "Loop.inl"