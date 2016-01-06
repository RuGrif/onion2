#pragma once


namespace QEdge_NS
{
  //  represent an edge in quad-edge structure
  template <typename T>
  class Loop
  {
  public:

    using Core = T;
    using Face = typename Core::Dual;
    using Edge = typename Core::Edge;
    using Dual = Loop<Face>;

    Loop( Dual& );
    ~Loop();

    const Loop& next() const { return *d_next; }
    Loop&       next()       { return *d_next; }

    const Dual& dual() const { return d_dual; }
    Dual&       dual()       { return d_dual; }

    Core&       core();

    void        fuse0( Loop& ); //  swap links and preserve this->o ring
    void        fuse1( Loop& ); //  swap links and preserve this->next->o ring

    void        splice0( Loop& ); //  preserve this->o and this->l rings
    void        splice1( Loop& ); //  preserve this->o and other->l rings

  private:

    void        attach( Core* );  //  merge this->core to other core
    void        detach();         //  split this->core from other core
    void        set( Core* );     //  update this->core

  private:

    Loop*       d_next = this;
    Dual&       d_dual;
    Core*       d_core = nullptr;

  private:

    Loop() = delete;
    Loop( const Loop& ) = delete;
    Loop& operator = ( const Loop& ) = delete;
  };
}


#include "Loop.inl"