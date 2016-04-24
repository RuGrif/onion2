#include "stdafx.h"
#include "CppUnitTest.h"
#include "Tetrahedron.h"
#include "Point3D.h"
#include "../QEdge/Utils.h"
#include "../Tailor/Cut.h"
#include "../IO/Mesh.h"
#include "../IO/STL.h"
#include "Intersection.h"
#include <set>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Cut )
  {
  public:

    TEST_METHOD( TetrahedronCut )
    {
      Test_NS::Tetrahedron x, y;

      x.a.o().reset<Test_NS::Point3D>( 1, 0, 0 );
      x.b.o().reset<Test_NS::Point3D>( 0, 1, 0 );
      x.c.o().reset<Test_NS::Point3D>( 0, 0, 1 );
      x.A.o().reset<Test_NS::Point3D>( 0, 0, 0 );

      y.a.o().reset<Test_NS::Point3D>( 2, 0, 0 );
      y.b.o().reset<Test_NS::Point3D>( 0, 2, 0 );
      y.c.o().reset<Test_NS::Point3D>( 0, 0, 2 );
      y.A.o().reset<Test_NS::Point3D>( 0.2, 0.2, 0.2 );

      QEdge_NS::Shape& a = x.d_shape;
      QEdge_NS::Shape& b = y.d_shape;

      IO_NS::writeMesh( a, L"Cut.A.in.mesh" );
      IO_NS::writeMesh( b, L"Cut.B.in.mesh" );

      Tailor_NS::cut( a, b );

      IO_NS::writeMesh( a, L"Cut.A.out.mesh" );
      IO_NS::writeMesh( b, L"Cut.B.out.mesh" );
    }


    TEST_METHOD( TorusCut )
    {
      QEdge_NS::Shape a = IO_NS::readSTL( L"triple torus.stl" );
      QEdge_NS::Shape b = IO_NS::readSTL( L"box.stl" );

      Tailor_NS::cut( a, b );

      IO_NS::writeMesh( a, L"Cut.Torus.mesh" );
      IO_NS::writeMesh( b, L"Cut.Box.mesh" );
    }
  };
}
