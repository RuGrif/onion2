#pragma once


#include "UniqueID.h"


namespace QEdge_NS
{
  //  represent an edge in quad-edge structure
  template <typename Traits>
  class Loop : public UniqueID
  {
  public:

    using Vert = typename Traits::Vert;
    using Face = typename Traits::Face;
    using Dual = Loop<typename Traits::Dual>;

    Loop( Dual& );
    ~Loop();

    const Loop& next() const { return *d_next; }
    Loop&       next()       { return *d_next; }

    const Dual& dual() const { return d_dual; }
    Dual&       dual()       { return d_dual; }

    Vert&       vert();           //  construct vert on demand

    void        fuse0( Loop& );   //  swap links and preserve this->o ring
    void        fuse1( Loop& );   //  swap links and preserve this->next->o ring

    void        splice0( Loop& ); //  preserve this->o and this->l rings
    void        splice1( Loop& ); //  preserve this->o and other->l rings

  private:

    void        attach( Vert* );  //  merge this->vert to other vert
    void        detach();         //  split this->vert from other vert
    void        set( Vert* );     //  update this->vert; doesn't manage resource

  private:

    Loop*       d_next = this;
    Dual&       d_dual;
    Vert*       d_core = nullptr;

  private:

    Loop() = delete;
    Loop( const Loop& ) = delete;
    Loop& operator = ( const Loop& ) = delete;
  };
}


#include "Loop.inl"