#pragma once


#include <string>
#include <exception>


namespace QEdge_NS
{
  class Tag
  {
  public:

    virtual std::wstring tag() const { return L"tag"; }

    virtual ~Tag() {}
  };


  class VertData : public Tag
  {
  public:

    virtual ~VertData() {}
  };


  class FaceData : public Tag
  {
  public:

    virtual ~FaceData() {}
  };


  class PrimEdgeData : public Tag
  {
  public:

    virtual ~PrimEdgeData() {}
  };


  class DualEdgeData : public Tag
  {
  public:

    virtual ~DualEdgeData() {}
  };
}