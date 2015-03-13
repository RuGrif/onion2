#pragma once


#include "..\QEdge\Edge.h"
#include <list>
#include <memory>
#include "Collision.h"


namespace Collision_NS
{
  //using Vec = Math_NS::Vector3L;


  struct COLLISION_API Prim
  {
    using Neighborhood =            std::list<std::unique_ptr<Prim>>;

    Prim( QEdge_NS::Edge i_edge ) : d_edge( i_edge ) {}
    
    virtual Neighborhood            neighbourhood() const = 0;
    virtual std::unique_ptr<Prim>   copy() const = 0;
    virtual size_t                  id() const = 0;

    virtual                         ~Prim() {}

  protected:

    QEdge_NS::Edge                  d_edge;
  };


  struct COLLISION_API Vert : public Prim
  {
    Vert( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    //Vec                             point() const;

    virtual Neighborhood            neighbourhood() const override;
    virtual std::unique_ptr<Prim>   copy() const override;
    virtual size_t                  id() const override;
  };


  struct COLLISION_API Edge : public Prim
  {
    Edge( QEdge_NS::Edge i_edge ) : Prim( i_edge ) {}

    //Vert                            A() const;
    //Vert                            B() const;

    virtual Neighborhood            neighbourhood() const override;
    virtual std::unique_ptr<Prim>   copy() const override;
    virtual size_t                  id() const override;
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
    virtual std::unique_ptr<Prim>   copy() const override;
    virtual size_t                  id() const override;
  };


  bool operator == ( const Prim&, const Prim& );
}