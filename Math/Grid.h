#pragma once


#include "Vector3.h"
#include "Math.h"


namespace Math_NS
{
  class MATH_API Grid
  {
  public:

    //  expect all points are within 10^6 * frame bbox
    Grid( const Vector3D& i_frame = Vector3D( 100, 100, 100 ) );

    Math_NS::Vector3L operator() ( const Math_NS::Vector3D& ) const;

  private:

    #pragma warning( suppress : 4251 )
    Math_NS::Vector3D d_scale;  //  scale factor used to map floats to integers
  };
}