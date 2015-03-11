#pragma once


#include "Edge.h"
#include "QEdge.h"
#include <iterator>


namespace QEdge_NS
{
  class QEDGE_API Shape
  {
  public:
    
    struct Impl;
    struct iterator;

    Shape();
    ~Shape();

    Edge makeEdge();
    Edge makeLoop();

    iterator begin();
    iterator end();

  private:

    Impl& impl;
  };


  class Quad;


  //struct Shape::iterator : std::iterator<std::bidirectional_iterator_tag, Edge>
  //{
  //  iterator& operator ++ ();
  //  iterator& operator -- ();

  //  Edge  operator *  () const;
  //  Edge* operator -> () const;

  //private:

  //  std::list<Quad>::iterator impl;
  //};
}