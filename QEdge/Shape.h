#pragma once


#include "Edge.h"
#include "Iterator.h"
#include "QEdge.h"


namespace QEdge_NS
{
  class QEDGE_API Shape
  {
  public:

    Shape();
    ~Shape();

    Edge makeEdge();
    Edge makeLoop();

    Iterator begin();
    Iterator end();

  public:

    struct Impl;
    Impl& impl() const;

  private:

    #pragma warning( suppress : 4251 )
    std::unique_ptr<Impl> d_pimpl; //  non-null
  };
}