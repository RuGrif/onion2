#pragma once


#include <string>
#include "..\Math\Vector3.h"
#include "QEdge.h"


namespace QEdge_NS
{
  struct Tag
  {
    //  get node comment
    virtual std::wstring tag() const { return L"tag"; }
    //  set node comment
    virtual void tag( const std::wstring& ) {}

    virtual ~Tag() {}
  };


  struct VertData : public Tag
  {
    virtual Math_NS::Vector3D point() const { return{}; }

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