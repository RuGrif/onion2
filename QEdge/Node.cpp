#include "Node.h"


namespace
{
  size_t makeNodeId()
  {
    static size_t s_uid = 0;
    return s_uid++;
  }
}


QEdge_NS::NodeId::NodeId() : d_uid( makeNodeId() ) {}
