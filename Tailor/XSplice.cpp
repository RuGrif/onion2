#include "XSplice.h"


void Tailor_NS::XSplice::operator()( QEdge_NS::Edge e, Segment&& s )
{
  d_edges.emplace( std::move( s ), e );
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
