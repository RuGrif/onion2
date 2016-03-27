#pragma once


#include "Vector3.h"
#include "Math.h"


namespace Math_NS
{
  class MATH_API Grid
  {
  public:

    Math_NS::Vector3L operator() ( const Math_NS::Vector3D& ) const;

  private:

    #pragma warning( suppress : 4251 )
    Math_NS::Vector3D d_scale{ 1E6, 1E6, 1E6 };  //  scale factor used to map floats to integers
  };
}