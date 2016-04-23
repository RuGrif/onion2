#pragma once


#include "Segment.h"
#include "Data.h"
#include "../Collision/XPoint.h"
#include <map>


namespace Tailor_NS
{
  class XSplice
  {
  public:

    void operator() ( QEdge_NS::Edge e, Segment&& s );

    template <typename A, typename B>
    void saveVert( const A& a, const B& b )
    {
      resetXPointData( d_vert, a, b );
    }

    void splice();

    void setVert();

  private:

    std::map<Segment, QEdge_NS::Edge> d_edges;
    QEdge_NS::Vert                    d_vert;
  };
}