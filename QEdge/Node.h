#pragma once


#include "Data.h"
#include "UniqueID.h"
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
  //  Traits
  //


  struct VertTraits;
  struct FaceTraits;


  struct VertTraits
  {
    using Vert = QEdge_NS::Vert;
    using Face = QEdge_NS::Face;
    using Edge = QEdge_NS::PrimEdge;
    using Dual = QEdge_NS::FaceTraits;
  };


  struct FaceTraits
  {
    using Vert = QEdge_NS::Face;
    using Face = QEdge_NS::Vert;
    using Edge = QEdge_NS::DualEdge;
    using Dual = QEdge_NS::VertTraits;
  };

  //
  //  Generic node type
  //

  struct Null : std::exception { virtual const char* what() const override { return "null node data"; } };


  template <typename Data>
  class Node : public UniqueID
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

    ~Node() = default;

  private:

    std::unique_ptr<Data> d_data;
  };


  template <typename Data> void swap( Node<Data>& a, Node<Data>& b ) { a.swap( b ); }

  //
  //  Concrete nodes implementation
  //

  struct Vert : public Node<VertData> {};
  struct Face : public Node<FaceData> {};
  struct PrimEdge : public Node<PrimEdgeData> {};
  struct DualEdge : public Node<DualEdgeData> {};
}


#include "Node.inl"