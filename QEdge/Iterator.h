#pragma once


#include <iterator>
#include "Edge.h"
#include <memory>


namespace QEdge_NS
{
  
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, Edge>
  {
  public:

    Iterator();
    Iterator( const Iterator& );
    Iterator& operator = ( const Iterator& );
    ~Iterator();

    Iterator& operator ++ ( );
    Iterator& operator -- ( );

    struct EPtr;

    Edge operator *  ( ) const;
    EPtr operator -> ( ) const;

    bool operator == ( const Iterator& ) const;
    bool operator != ( const Iterator& ) const;

  public:

    struct Impl;
    Impl& impl() const;

  private:

    std::unique_ptr<Impl> d_pimpl;
  };


  struct Iterator::EPtr : private Edge
  {
    EPtr( Edge e ) : Edge( e ) {}
    Edge* operator -> () { return this; }
  };
}