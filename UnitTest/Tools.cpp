#include "stdafx.h"
#include "Tools.h"


void label( QEdge_NS::Edge e, const std::wstring& i_name )
{
  if( e )
  {
    e.n().reset<QEdge_NS::DebugData>( i_name );
    e.s().reset<QEdge_NS::DebugData>( i_name + L".sym" );
    e.e().reset<QEdge_NS::DebugData>( i_name + L".inv" );
    e.w().reset<QEdge_NS::DebugData>( i_name + L".rot" );

    e.d().reset<QEdge_NS::DebugData>( i_name + L".d" );
    e.o().reset<QEdge_NS::DebugData>( i_name + L".o" );
    e.r().reset<QEdge_NS::DebugData>( i_name + L".r" );
    e.l().reset<QEdge_NS::DebugData>( i_name + L".l" );
  }
}