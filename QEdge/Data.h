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


  template <typename T>
  struct Point3
  {
    //  get point coordinates
    virtual Math_NS::Vector3<T> point() const { return{}; }
    //  set point coordinates
    virtual void point( const Math_NS::Vector3<T>& ) {}

    virtual ~Point3() {}
  };


  struct VertData : public Tag, public Point3<double>
  {
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