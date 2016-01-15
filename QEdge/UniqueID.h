#pragma once


#include "QEdge.h"


namespace QEdge_NS
{
  QEDGE_API size_t makeUniqueID();

  class UniqueID
  {
    const size_t d_uid = makeUniqueID();
  public:
    const size_t id() const { return d_uid; }
  };
}