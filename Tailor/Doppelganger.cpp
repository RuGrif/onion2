#include "Doppelganger.h"


void Tailor_NS::TwinEdge::insert( const Int& u, const Int& v, const Math_NS::Vector3D& p, const XID& xid )
{
  Position pos = std::make_pair( Math_NS::makeRational( v, u + v ), xid );

  auto i = d_twin.emplace( pos, p );

  if( !i.second ) throw DuplicatedIntersectionPoint{ xid };
}


Tailor_NS::TwinEdge::Map Tailor_NS::TwinEdge::forgery( QEdge_NS::Shape& io_shape ) const
{
  Map edges;

  QEdge_NS::Edge prev = io_shape.makeEdge();

  //  construct a chain of new edges, starting from a given one
  for( const auto& t : d_twin )
  {
    QEdge_NS::Edge next = io_shape.makeEdge();  //  new link in the chain
    prev.sym().splice0( next );                 //  attach new link to last link in a chain
    next.o().reset<TwinStar>( t.second );       //  set geometrical data
    edges[ t.first.second ] = next;             //  memorize XID -> Edge function
    prev = next;                                //  move to next iteration
  }

  return edges;
}


void Tailor_NS::TwinEdgeCollection::insert( const Collision_NS::XEdge& x, const Math_NS::Vector3D& p, const Collision_NS::XPointID& xid )
{
  TwinEdge& twin = d_collection[ x ];
  
  if( x.isMajor() )
  {
    twin.insert( x.u, x.v, p, xid );
  }
  else
  {
    twin.insert( x.v, x.u, p, xid );
  }
}


Tailor_NS::TwinEdgeCollection::Map Tailor_NS::TwinEdgeCollection::forgery( QEdge_NS::Shape& io_shape ) const
{
  Map edges;

  for( const auto& t : d_collection )
  {
    edges.emplace(
      t.first.isMajor() ? t.first.e() : t.first.e().sym(),
      t.second.forgery( io_shape ) );
  }

  return edges;
}