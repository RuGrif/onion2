#pragma once


namespace Tailor_NS
{
  struct DuplicatedMapEntry : std::exception
  {
    DuplicatedMapEntry( size_t id0 = 0, size_t id1 = 0 ) : d_id0{ id0 }, d_id1{ id1 } {}
    
    virtual const char* what() const override { return "Duplicated map entry"; }
    
    const size_t d_id0;
    const size_t d_id1;
  };
}