#pragma once


#include <string>
#include "Vector.h"
#include "QEdge.h"


namespace QEdge_NS
{
  class QEDGE_API Tag
  {
  public:

    virtual std::wstring tag() const;

    virtual ~Tag();
  };


  class QEDGE_API VertData : public Tag
  {
  public:

    //  get vertex coordinates
    virtual Vector3D point() const;
    //  set vertex coordinates
    virtual void point( const Vector3D& );

    virtual ~VertData();
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