#pragma once


#include "..\QEdge\Edge.h"
#include <vector>
#include <memory>
#include "Collision.h"


namespace Collision_NS
{
  struct COLLISION_API Prim
  {
    using Neighborhood =            std::vector<size_t>;

    Prim( QEdge_NS::Edge i_edge ) : d_edge( i_edge ) {}
    
    virtual Neighborhood            neighbourhood() const = 0;
    virtual                         operator size_t() const = 0;
    virtual std::unique_ptr<Prim>   clone() const = 0;

    virtual                         ~Prim() {}

  protected:

    QEdge_NS::Edge                  d_edge;
  };


  struct COLLISION_API Vert : public Prim
  {
    Vert( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    Math_NS::Vector3D               point() const { return d_edge.o()->point(); }

    virtual Neighborhood            neighbourhood() const override;
    virtual                         operator size_t() const override;
    virtual std::unique_ptr<Prim>   clone() const override;
  };


  struct COLLISION_API Edge : public Prim
  {
    Edge( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    Vert                            U() const { return d_edge; }
    Vert                            V() const { return d_edge.sym(); }

    virtual Neighborhood            neighbourhood() const override;
    virtual                         operator size_t() const override;
    virtual std::unique_ptr<Prim>   clone() const override;
  };


  struct COLLISION_API Face : public Prim
  {
    Face( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    Edge                            AB() const { return d_edge; }
    Edge                            BC() const { return d_edge.lNext(); }
    Edge                            CA() const { return d_edge.lPrev(); }

    Vert                            A() const { return d_edge; }
    Vert                            B() const { return d_edge.lNext(); }
    Vert                            C() const { return d_edge.lPrev(); }

    virtual Neighborhood            neighbourhood() const override;
    virtual                         operator size_t() const override;
    virtual std::unique_ptr<Prim>   clone() const override;
  };


  bool operator == ( const Prim&, const Prim& );
}