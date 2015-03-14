#pragma once


#include "..\QEdge\Edge.h"
#include <vector>
#include "Collision.h"


namespace Collision_NS
{
  //using Vec = Math_NS::Vector3L;


  struct COLLISION_API Prim
  {
    using Neighborhood =            std::vector<size_t>;

    Prim( QEdge_NS::Edge i_edge ) : d_edge( i_edge ) {}
    
    virtual Neighborhood            neighbourhood() const = 0;
    virtual                         operator size_t() const = 0;

    virtual                         ~Prim() {}

  protected:

    QEdge_NS::Edge                  d_edge;
  };


  struct COLLISION_API Vert : public Prim
  {
    Vert( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    //Vec                             point() const;

    virtual Neighborhood            neighbourhood() const override;
    virtual                         operator size_t() const override;
  };


  struct COLLISION_API Edge : public Prim
  {
    Edge( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    //Vert                            A() const;
    //Vert                            B() const;

    virtual Neighborhood            neighbourhood() const override;
    virtual                         operator size_t() const override;
  };


  struct COLLISION_API Face : public Prim
  {
    Face( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    //Vert                            A() const;
    //Vert                            B() const;
    //Vert                            C() const;

    //Edge                            AB() const;
    //Edge                            BC() const;
    //Edge                            CA() const;

    virtual Neighborhood            neighbourhood() const override;
    virtual                         operator size_t() const override;
  };


  bool operator == ( const Prim&, const Prim& );
}