#pragma once


#include <iterator>
#include "Edge.h"
#include <memory>
#include "QEdge.h"


namespace QEdge_NS
{
  class QEDGE_API Iterator : std::iterator<std::bidirectional_iterator_tag, Edge>
  {
  public:

    Iterator();
    Iterator( const Iterator& ) = default;
    Iterator& operator = ( const Iterator& ) = default;
    ~Iterator();

    Iterator& operator ++ ( );
    Iterator& operator -- ( );

    Edge operator *  ( ) const;
    Edge operator -> ( ) const;

    bool operator == ( const Iterator& ) const;
    bool operator != ( const Iterator& ) const;

  public:

    struct Impl;
    Impl& impl() const;

  private:

    #pragma warning( suppress : 4251 )
    std::shared_ptr<Impl> d_pimpl;
  };
}