#include "../QEdge/Data.h"
#include "../Math/Vector3.h"


namespace Test_NS
{
  struct Point3D : public QEdge_NS::VertData
  {
    Point3D() = default;
    Point3D( const Math_NS::Vector3D& i_point ) : d_point( i_point ) {}
    Point3D( double x, double y, double z ) : d_point( x, y, z ) {}

    virtual const Math_NS::Vector3D point() const override { return d_point; }

  private:

    Math_NS::Vector3D d_point;
  };
}