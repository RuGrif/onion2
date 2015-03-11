#pragma once


#include "Data.h"
#include <memory>
#include <exception>


namespace QEdge_NS
{
  //
  //  Concrete nodes declaration
  //

  struct Vert;
  struct Face;
  struct PrimEdge;
  struct DualEdge;

  //
  //  Generic node type
  //

  struct Null : std::exception { virtual const char* what() const override { return "null node data"; } };


  template <typename Data>
  class Node
  {
  public:

    //  initialize node data
    template <typename T, typename ... Args> void reset( Args&& ... );

    //  exchange node data
    void swap( Node& );

    //  access node data

    operator bool() const;

    struct Null : QEdge_NS::Null {};

    const Data& operator *  () const;
    Data&       operator *  ();
    
    const Data* operator -> () const;
    Data*       operator -> ();

  protected:

    ~Node(){}

  private:

    std::unique_ptr<Data> d_data;
  };


  template <typename Data> void swap( Node<Data>& a, Node<Data>& b ) { a.swap( b ); }

  //
  //  Concrete nodes implementation
  //

  struct Vert : public Node<VertData>
  {
    using Edge = QEdge_NS::PrimEdge;
    using Dual = QEdge_NS::Face;
  };


  struct Face : public Node<FaceData>
  {
    using Edge = QEdge_NS::DualEdge;
    using Dual = QEdge_NS::Vert;
  };


  struct PrimEdge : public Node<PrimEdgeData>
  {
    using Vert = QEdge_NS::Vert;
    using Dual = Vert::Dual::Edge;
  };


  struct DualEdge : public Node<DualEdgeData>
  {
    using Vert = QEdge_NS::Face;
    using Dual = Vert::Dual::Edge;
  };
}


#include "Node.inl"