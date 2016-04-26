#pragma once


#include "Ray.h"
#include "Data.h"
#include "../Collision/XPoint.h"
#include <map>


namespace Tailor_NS
{
  struct EmptyXSplice : std::exception
  {
    EmptyXSplice( size_t id ) : id{ id } {}

    virtual const char* what() const override { return "Empty XSplice edge collection"; }

    const size_t id;
  };


  class XSplice
  {
  public:

    void operator() ( QEdge_NS::Edge, Ray&& );

    template <typename A, typename B>
    void saveVert( const A& a, const B& b )
    {
      resetXPointData( d_vert, a, b );
    }

    void splice();

    void setVert();

  private:

    std::map<Ray, QEdge_NS::Edge> d_edges;
    QEdge_NS::Vert                d_vert;
  };
}