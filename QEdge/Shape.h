#pragma once


#include "Edge.h"
#include "Iterator.h"


namespace QEdge_NS
{
  class Shape
  {
  public:

    Shape();
    Shape( Shape&& );
    Shape& operator = ( Shape&& );
    ~Shape();

    Edge makeEdge();
    Edge makeLoop();

    Iterator begin() const;
    Iterator end() const;

    size_t size() const;

  public:

    struct Impl;
    Impl& impl() const;

    Shape( const Shape& ) = delete;
    Shape& operator = ( const Shape& ) = delete;

  private:

    std::unique_ptr<Impl> d_pimpl; //  non-null
  };
}