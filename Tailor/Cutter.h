#pragma once


#include "../QEdge/Shape.h"
#include "../Collision/Intersection.h"
#include <map>
#include "Tailor.h"


namespace Tailor_NS
{
  class TAILOR_API Cutter
  {
  public:

    template <typename P0, typename P1>
    QEdge_NS::Edge add( const P0& p0, const P1& p1 )
    {
      return getOrCreate( p0, p1 );
    }

  private:

    template <typename A, typename B>
    QEdge_NS::Edge getOrCreate( const A& a, const B& b )
    {
      //  look for existing p0-p1 edge
      {
        auto f = d_edges.find( Collision_NS::makeXPointID( a, b ) );
        if( f != d_edges.end() ) return f->second;
      }

      //  look for existing p1-p0 edge
      {
        auto f = d_edges.find( Collision_NS::makeXPointID( b, a ) );
        if( f != d_edges.end() ) return f->second.sym();
      }

      //  create new edge
      auto f = d_edges.emplace( Collision_NS::makeXPointID( a, b ), d_cut.makeEdge() );
      return f.first->second;
    }
    
  //private:
  public:

    std::map<Collision_NS::XPointID, QEdge_NS::Edge>      d_edges;
    QEdge_NS::Shape                                       d_cut;
    //QEdge_NS::Shape&                                      d_shape;
  };
}