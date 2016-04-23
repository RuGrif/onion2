#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Tailor/Segment.h"
#include "Tetrahedron.h"
#include "Point3D.h"
#include <algorithm>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( Orbit )
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

    TEST_METHOD( Face )
    {
      auto t = makeTetra();

      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.a }, F{ t.a } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.b }, F{ t.a } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.c }, F{ t.a } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.a }, F{ t.b } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.b }, F{ t.b } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.c }, F{ t.b } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.a }, F{ t.c } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.b }, F{ t.c } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.c }, F{ t.c } ) );
    }

    TEST_METHOD( Edge )
    {
      auto t = makeTetra();

      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.a }, E{ t.a } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.a }, E{ t.a.sym() } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.b }, E{ t.a } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.b }, E{ t.a.sym() } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.c }, E{ t.a } ) );
      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ t.c }, E{ t.a.sym() } ) );

      Assert::AreEqual( 1u, Tailor_NS::orbit( F{ t.a.sym() }, E{ t.a } ) );
      Assert::AreEqual( 1u, Tailor_NS::orbit( F{ t.a.sym() }, E{ t.a.sym() } ) );
    }

    TEST_METHOD( Vert )
    {
      auto t = makeTetra();

      std::vector<E> e = { t.a, t.a.oNext(), t.a.oNext().oNext() };
      std::rotate( e.begin(), std::min_element( e.begin(), e.end() ), e.end() );

      Assert::AreEqual( 0u, Tailor_NS::orbit( F{ e[ 0 ].e() }, V{ t.a } ) );
      Assert::AreEqual( 1u, Tailor_NS::orbit( F{ e[ 1 ].e() }, V{ t.a } ) );
      Assert::AreEqual( 2u, Tailor_NS::orbit( F{ e[ 2 ].e() }, V{ t.a } ) );
    }
  };
}