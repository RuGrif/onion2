#pragma once


#include "Vector3.h"
#include "Box3.h"


namespace Math_NS
{
  class Grid
  {
  public:

    Grid( const Math_NS::Box3D& );

    Math_NS::Vector3L operator() ( const Math_NS::Vector3D& ) const;

  private:

    const Math_NS::Vector3D d_zero;
    const Math_NS::Vector3D d_diag;
  };
}