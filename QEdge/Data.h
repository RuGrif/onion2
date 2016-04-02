#pragma once


#include <string>
#include "../Math/Vector3.h"


namespace QEdge_NS
{
  struct Tag
  {
    virtual std::wstring tag() const { return L"tag"; }
    virtual ~Tag() {}
  };


  struct VertData : public Tag
  {
    virtual const Math_NS::Vector3D point() const = 0;
    virtual ~VertData() {}
  };


  struct FaceData : public Tag
  {
    virtual ~FaceData() {}
  };


  struct PrimEdgeData : public Tag
  {
    virtual ~PrimEdgeData() {}
  };


  struct DualEdgeData : public Tag
  {
    virtual ~DualEdgeData() {}
  };
}