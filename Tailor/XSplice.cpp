#include "XSplice.h"
#include "checked_insert.h"


void Tailor_NS::XSplice::operator()( QEdge_NS::Edge e, Segment&& s )
{
  auto i = d_edges.emplace( std::move( s ), e );

  if( !i.second ) throw DuplicatedMapEntry{ s.sid().first, s.sid().second };
}


void Tailor_NS::XSplice::splice()
{
  if( !d_edges.empty() )
  {
    for( auto i = std::next( d_edges.begin() ); i != d_edges.end(); ++i )
    {
      i->second.splice0( std::prev( i )->second );
    }
  }
}


void Tailor_NS::XSplice::setVert()
{
  if( !d_edges.empty() )
  {
    d_edges.begin()->second.o().swap( d_vert );
  }
}
