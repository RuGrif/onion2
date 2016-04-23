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

    Iterator begin() const; //  iterate edges
    Iterator end() const;   //  iterate edges

    size_t size() const;    //  return number of edges

    void cleanup();         //  remove edges with no vertex information

    void merge( Shape&& );  //  move all edges from other shape to this one

  public:

    struct Impl;
    Impl& impl() const;

    Shape( const Shape& ) = delete;
    Shape& operator = ( const Shape& ) = delete;

  private:

    std::unique_ptr<Impl> d_pimpl; //  non-null
  };
}