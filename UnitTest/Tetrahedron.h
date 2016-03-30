#pragma once


#include "../QEdge/Shape.h"


namespace Test_NS
{
  struct Tetrahedron
  {
    QEdge_NS::Shape d_shape;
    
    //  base triangle abc (a->b->c is positive orientation)
    QEdge_NS::Edge a = d_shape.makeEdge();
    QEdge_NS::Edge b = d_shape.makeEdge();
    QEdge_NS::Edge c = d_shape.makeEdge();

    //  B.o = A.o = C.o = top vertex
    QEdge_NS::Edge A = d_shape.makeEdge();  //  opposite to a
    QEdge_NS::Edge B = d_shape.makeEdge();  //  opposite to b
    QEdge_NS::Edge C = d_shape.makeEdge();  //  opposite to c

    Tetrahedron();
  };
}