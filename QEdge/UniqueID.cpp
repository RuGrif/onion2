#include "UniqueID.h"


size_t QEdge_NS::makeUniqueID()
{
  static size_t s_uid = 0;
  return s_uid++;
}
