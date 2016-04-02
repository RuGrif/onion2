#pragma once


#include "../QEdge/Data.h"


namespace QEdge_NS
{
  class DebugData : public VertData, public FaceData, public PrimEdgeData, public DualEdgeData
  {
    std::wstring d_tag;

  public:

    DebugData( const std::wstring& i_tag = L"debug tag" ) : d_tag( i_tag ) {}

    virtual std::wstring tag() const override { return d_tag; }
    virtual const Math_NS::Vector3D point() const override { return{}; }
  };
}