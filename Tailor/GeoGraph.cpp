#include "GeoGraph.h"


void Tailor_NS::GeoGraph::add( const XID& p0, const Loc& loc0, const EID& e, const XID& p1, const Loc& loc1 )
{
  GeoEdge& g = d_edges[ e ];
  g.o = p0;
  g.d = p1;

  GeoVert& v0 = d_verts[ g.o ];
  v0.d_edges.push_back( e );

  GeoVert& v1 = d_verts[ g.d ];
  v1.d_edges.push_back( e );
}


Tailor_NS::GeoGraph::GeoVert::GeoVert( const Collision_NS::XVert& v ) : GeoVert{ GeoLocationCCW{ v } }
{
  QEdge_NS::Edge e = v.e();
  do
  {
    Collision_NS::Edge ray{ e };
    d_edges.insert(  )
  }
}