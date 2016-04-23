#pragma once


#include "XSplice.h"
#include <list>


namespace Tailor_NS
{
  class DeferSplice
  {
  public:

    void spliceOrDefer( XSplice&&, const Collision_NS::XVert& );
    void spliceOrDefer( XSplice&&, const Collision_NS::XEdge& );
    void spliceOrDefer( XSplice&&, const Collision_NS::XFace& );
    
    void splice();

  public:

    const auto& collection() const { return d_splices; }  //  for unit tests

  private:

    void defer( XSplice&& );

  private:

    std::list<XSplice> d_splices;
  };
}