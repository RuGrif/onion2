#include "Doppelganger.h"


void Tailor_NS::TwinEdge::insert( const Int& u, const Int& v, const Math_NS::Vector3D& p, const Collision_NS::XPointID& xid )
{
  Position pos = std::make_pair( Math_NS::makeRational( u, u + v ), xid );

  auto i = d_twin.emplace( pos, p );

  if( !i.second ) throw DuplicatedIntersectionPoint{ xid };
}


void Tailor_NS::TwinEdge::forgery( QEdge_NS::Shape& io_shape, QEdge_NS::Edge i_edge ) const
{
  QEdge_NS::Edge prev = i_edge;
  QEdge_NS::Edge dest = prev.sym().oPrev();

  //  detach edge.d
  dest.splice0( prev.sym() );

  //  construct a chain of new edges, starting from a given one
  for( const auto& t : d_twin )
  {
    QEdge_NS::Edge next = io_shape.makeEdge();
    
    prev.sym().splice0( next );
    
    next.o().reset<TwinStar>( t.second );
    
    prev = next;
  }

  //  attach new edge.d back
  dest.splice0( prev.sym() );
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


void Tailor_NS::TwinEdgeCollection::forgery( QEdge_NS::Shape& io_shape ) const
{
  for( const auto& t : d_collection )
  {
    t.second.forgery( io_shape, t.first.isMajor() ? t.first.e() : t.first.e().sym() );
  }
}