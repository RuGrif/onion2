#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Tailor/Ray.h"
#include "Tetrahedron.h"
#include "Point3D.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Ray )
  {
    auto makeTetra()
    {
      Test_NS::Tetrahedron t;

      t.a.o().reset<Test_NS::Point3D>( 1, 0, 0 );
      t.b.o().reset<Test_NS::Point3D>( 0, 1, 0 );
      t.c.o().reset<Test_NS::Point3D>( 0, 0, 1 );
      t.A.o().reset<Test_NS::Point3D>( 0, 0, 0 );

      return t;
    }

    using V = Collision_NS::Vert;
    using E = Collision_NS::Edge;
    using F = Collision_NS::Face;

  public:

    TEST_METHOD( Edge )
    {
      auto t = makeTetra();

      Tailor_NS::Ray s0{ E{ t.a } };
      Tailor_NS::Ray s1{ E{ t.a.sym() } };

      Assert::IsTrue( s0 < s1 || s1 < s0 );
    }

    TEST_METHOD( Vert )
    {
      auto t = makeTetra();

      Tailor_NS::Ray s0{ V{ t.a } };
      Tailor_NS::Ray s1{ V{ t.a.oNext() } };
      Tailor_NS::Ray s2{ V{ t.a.oNext().oNext() } };

      Assert::IsTrue(
        ( s0 < s1 && s1 < s2 ) ||
        ( s1 < s2 && s2 < s0 ) ||
        ( s2 < s0 && s0 < s1 )
      );
    }
  };
}