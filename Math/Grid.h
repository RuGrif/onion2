#pragma once


#include "Vector3.h"
#include "Box3.h"
#include "Math.h"


namespace Math_NS
{
  class MATH_API Grid
  {
  public:

    Grid( const Math_NS::Box3D& i_box ) : d_box{ i_box } {}
    Math_NS::Vector3L operator() ( const Math_NS::Vector3D& ) const;

  private:

    #pragma warning( suppress : 4251 )
    const Math_NS::Box3D d_box;
  };
}