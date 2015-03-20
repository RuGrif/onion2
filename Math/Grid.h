#pragma once


#include "Vector3.h"
#include "Box3.h"


namespace Math_NS
{
  class Grid
  {
  public:

    Grid( const Box3D& i_box, const Vector3D& i_frame );

    Math_NS::Vector3L operator() ( const Math_NS::Vector3D& ) const;

  private:

    Math_NS::Vector3D d_center; //  center of a bounding box
    Math_NS::Vector3D d_scale;  //  scale factor used to map floats to integers
  };
}