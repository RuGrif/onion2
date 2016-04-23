#include "DeferSplice.h"


void Tailor_NS::DeferSplice::defer( XSplice&& i_splice )
{
  d_splices.emplace_front( std::move( i_splice ) );
}


void Tailor_NS::DeferSplice::spliceOrDefer( XSplice&& i_splice, const Collision_NS::XVert& i_vert )
{
  QEdge_NS::Edge e = i_vert.e();
  do
  {
    i_splice( e, Segment{ Collision_NS::Vert{ e } } );
  }
  while( ( e = e.oNext() ) != i_vert.e() );

  defer( std::move( i_splice ) );
}


void Tailor_NS::DeferSplice::spliceOrDefer( XSplice&& i_splice, const Collision_NS::XEdge& i_edge )
{
  defer( std::move( i_splice ) );
}


void Tailor_NS::DeferSplice::spliceOrDefer( XSplice&& i_splice, const Collision_NS::XFace& )
{
  i_splice.splice();
  i_splice.setVert();
}


void Tailor_NS::DeferSplice::splice()
{
  for( XSplice& xs : d_splices ) xs.splice();
  for( XSplice& xs : d_splices ) xs.setVert();
}