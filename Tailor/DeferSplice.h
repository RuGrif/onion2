#pragma once


#include "XSplice.h"
#include <forward_list>


namespace Tailor_NS
{
  class DeferSplice
  {
  public:

    void spliceOrDefer( XSplice&&, const Collision_NS::XVert& );
    void spliceOrDefer( XSplice&&, const Collision_NS::XEdge& );
    void spliceOrDefer( XSplice&&, const Collision_NS::XFace& );
    
    void splice();

  private:

    void defer( XSplice&& );

  private:

    std::forward_list<XSplice> d_splices;
  };
}