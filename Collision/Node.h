#pragma once


#include "Primitive.h"
#include <memory>
#include "Collision.h"


namespace Collision_NS
{
  using NodeId = std::pair<size_t, size_t>;

  //  Intersection vertex
  class COLLISION_API Node
  {
    Node() = delete;
    Node( const Node& ) = delete;
    Node& operator = ( const Node& ) = delete;

  public:

    using Int = Prim::Int;

    Node( Node&& );
    Node& operator = ( Node&& );

    Node( std::unique_ptr<Prim>&&, std::unique_ptr<Prim>&& );

    Prim& alpha() const { return *d_alpha; }
    Prim& beta() const { return *d_beta; }

    void alter() { std::swap( d_alpha, d_beta ); }

    NodeId id() const { return{ alpha(), beta() }; }

    ~Node();

  private:
    
    #pragma warning( suppress : 4251 )
    std::unique_ptr<Prim>     d_alpha;

    #pragma warning( suppress : 4251 )
    std::unique_ptr<Prim>     d_beta;
    
  };


  bool operator == ( const Node&, const Node& );
}


template <> struct std::hash<Collision_NS::NodeId>
{
  std::size_t operator() ( const Collision_NS::NodeId& ) const;
};
