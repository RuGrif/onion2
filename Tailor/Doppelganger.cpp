#include "Doppelganger.h"
#include "checked_insert.h"


void Tailor_NS::TwinEdge::insert( const Int& u, const Int& v, const XID& xid )
{
  auto i = d_verts.emplace( Math_NS::makeRational( v, u + v ), xid );
  
  if( !i.second ) throw DuplicatedMapEntry{ xid.first, xid.second };
}


void Tailor_NS::TwinEdge::makeTwins( QEdge_NS::Shape& io_shape )
{
  QEdge_NS::Edge prev = io_shape.makeEdge();

  for( const auto& t : d_verts )
  {
    QEdge_NS::Edge next = io_shape.makeEdge();
    d_edges[ t.second ] = std::make_pair( prev.sym(), next );
    prev = next;
  }
}


Tailor_NS::TwinEdge::EdgePair Tailor_NS::TwinEdge::edgePair( const XID& i_xid ) const
{
  return d_edges.at( i_xid );
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

  XID first = d_verts.begin()->second;
  XID last = d_verts.rbegin()->second;

  sub( e,       edgePair( first ).first.sym() );
  sub( e.sym(), edgePair( last ).second.sym() );
}


void Tailor_NS::TwinEdgeCollection::insert( const Collision_NS::XEdge& x, const Collision_NS::XPointID& xid )
{
  auto i = d_collection.find( id( x ) );

  if( i == d_collection.end() )
  {
    Collision_NS::Edge m = x.isMajor() ? x : Collision_NS::Edge{ x.e().sym() };
    i = d_collection.emplace( id( x ), std::make_pair( m, TwinEdge{} ) ).first;
  }

  if( x.isMajor() )
  {
    i->second.second.insert( x.u, x.v, xid );
  }
  else
  {
    i->second.second.insert( x.v, x.u, xid );
  }
}


void Tailor_NS::TwinEdgeCollection::makeTwins()
{
  for( auto& t : d_collection )
  {
    t.second.second.makeTwins( d_twin );
  }
}


const Tailor_NS::TwinEdge& Tailor_NS::TwinEdgeCollection::twinEdge( size_t eid ) const
{
  return d_collection.at( eid ).second;
}


void Tailor_NS::TwinEdgeCollection::substitute() const
{
  for( auto& t : d_collection )
  {
    t.second.second.substitute( t.second.first.e() );
  }
}


void Tailor_NS::Doppelganger::shadow( const TopoGraph & g )
{
  g.forEachXPoint( std::ref( *this ) );
}


void Tailor_NS::Doppelganger::makeTwins()
{
  d_doppelA.makeTwins();
  d_doppelB.makeTwins();
}


void Tailor_NS::Doppelganger::substitute() const
{
  d_doppelA.substitute();
  d_doppelB.substitute();
}


template <typename A, typename B>
void Tailor_NS::Doppelganger::operator() ( const Collision_NS::XPoint<A, B>& v )
{
  d_doppelA.insert( v.first,  Collision_NS::makeXPointID( v.first, v.second ) );
  d_doppelB.insert( v.second, Collision_NS::makeXPointID( v.second, v.first ) );
}