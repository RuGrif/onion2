#pragma once


#include "Data.h"
#include <exception>


namespace QEdge_NS
{
  class DebugData : virtual public VertData, virtual public FaceData, virtual public PrimEdgeData, virtual public DualEdgeData
  {
    std::wstring d_tag;

  public:

    DebugData( const std::wstring& i_tag = L"debug tag" ) : d_tag( i_tag ) {}

    virtual std::wstring tag() const override { return d_tag; }
  };
}