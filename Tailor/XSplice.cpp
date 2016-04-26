#include "XSplice.h"
#include "checked_insert.h"


void Tailor_NS::XSplice::operator()( QEdge_NS::Edge e, Ray&& r )
{
  auto i = d_edges.emplace( std::move( r ), e );

  if( !i.second ) throw DuplicatedMapEntry{ r.pid1().first, r.pid1().second };
}


void Tailor_NS::XSplice::splice()
{
  if( d_edges.empty() ) throw EmptyXSplice{};

  for( auto i = std::next( d_edges.begin() ); i != d_edges.end(); ++i )
  {
    QEdge_NS::Edge prev = std::prev( i )->second;
    QEdge_NS::Edge next = i->second;

    if( prev.oNext() != next )
    {
      next.splice0( prev );
    }
  }
}


void Tailor_NS::XSplice::setVert()
{
  if( d_edges.empty() ) throw EmptyXSplice{};
  
  d_edges.begin()->second.o().swap( d_vert );
}
