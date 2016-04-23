#include "Doppelganger.h"


void Tailor_NS::TwinEdge::insert( const Int& u, const Int& v, const Math_NS::Vector3D& p, const XID& xid )
{
  Position pos = std::make_pair( Math_NS::makeRational( v, u + v ), xid );

  auto i = d_verts.emplace( pos, p );

  if( !i.second ) throw DuplicatedIntersectionPoint{ xid };
}


void Tailor_NS::TwinEdge::makeTwins( QEdge_NS::Shape& io_shape )
{
  QEdge_NS::Edge prev = io_shape.makeEdge();

  for( const auto& t : d_verts )
  {
    QEdge_NS::Edge next = io_shape.makeEdge();
    d_edges[ t.first.second ] = std::make_pair( prev.sym(), next );
    prev = next;
  }
}


QEdge_NS::Edge Tailor_NS::TwinEdge::prev( const XID& i_xid ) const
{
  return d_edges.at( i_xid ).first;
}


QEdge_NS::Edge Tailor_NS::TwinEdge::next( const XID& i_xid ) const
{
  return d_edges.at( i_xid ).second;
}


void Tailor_NS::TwinEdge::substitute( QEdge_NS::Edge e ) const
{
  auto sub = []( QEdge_NS::Edge who, QEdge_NS::Edge with )
  {
    QEdge_NS::Edge prev = who.oPrev();
    prev.splice0( who );
    prev.splice0( with );
  };

  if( d_verts.empty() ) throw std::logic_error( __FUNCTION__ );

  XID first = d_verts.begin()->first.second;
  XID last = d_verts.rbegin()->first.second;

  sub( e, prev( first ).sym() );
  sub( e.sym(), next( last ).sym() );
}


void Tailor_NS::TwinEdgeCollection::insert( const Collision_NS::XEdge& x, const Math_NS::Vector3D& p, const Collision_NS::XPointID& xid )
{
  if( x.isMajor() )
  {
    auto i = d_collection.emplace( id( x ), std::make_pair( x, TwinEdge{} ) );
    i.first->second.second.insert( x.u, x.v, p, xid );
  }
  else
  {
    Collision_NS::Edge y{ x.e().sym() };
    auto i = d_collection.emplace( id( x ), std::make_pair( y, TwinEdge{} ) );
    i.first->second.second.insert( x.v, x.u, p, xid );
  }
}


void Tailor_NS::TwinEdgeCollection::makeTwins( QEdge_NS::Shape& io_shape )
{
  for( auto& t : d_collection )
  {
    t.second.second.makeTwins( io_shape );
  }
}


QEdge_NS::Edge Tailor_NS::TwinEdgeCollection::prev( const Collision_NS::XPointID& i_xid ) const
{
  return d_collection.at( i_xid.first ).second.prev( i_xid );
}


QEdge_NS::Edge Tailor_NS::TwinEdgeCollection::next( const Collision_NS::XPointID& i_xid ) const
{
  return d_collection.at( i_xid.first ).second.next( i_xid );
}


void Tailor_NS::TwinEdgeCollection::substitute() const
{
  for( auto& t : d_collection )
  {
    t.second.second.substitute( t.second.first.e() );
  }
}


void Tailor_NS::Doppelganger::makeTwins( QEdge_NS::Shape& a, QEdge_NS::Shape& b )
{
  d_doppelA.makeTwins( a );
  d_doppelB.makeTwins( b );
}


void Tailor_NS::Doppelganger::substitute() const
{
  d_doppelA.substitute();
  d_doppelB.substitute();
}
