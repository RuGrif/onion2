#pragma once


namespace QEdge_NS
{
  size_t makeUniqueID();

  class UniqueID
  {
    const size_t d_id = makeUniqueID();
  public:
    const size_t id() const { return d_id; }
  };
}