#pragma once


#include "../QEdge/Edge.h"
#include "Primitive.h"
#include <map>
#include <vector>


namespace Collision_NS
{
  using XVertID = std::pair<size_t, size_t>;

  struct YVertID
  {
    std::vector<size_t> alpha;
    std::vector<size_t> beta;
    QEdge_NS::Edge      edge;

    template <typename A, typename B>
    YVertID( const A& a, const B& b, QEdge_NS::Edge e ) : alpha{ nb( a ) }, beta{ nb( b ) }, edge{ e } {}
  };

  using Connection = std::map<XVertID, YVertID>;
}
