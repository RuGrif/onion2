#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Collision/XPoint.h"
#include "Tetrahedron.h"
#include "Point3D.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{
  TEST_CLASS( XPoint )
  {
    Math_NS::Vector3D fpoint( const Collision_NS::XFace& f )
    {
      return (
        static_cast<double>( f.a ) * f.A().point() +
        static_cast<double>( f.b ) * f.B().point() +
        static_cast<double>( f.c ) * f.C().point() ) / static_cast<double>( f.a + f.b + f.c );
    }

  public:

    TEST_METHOD( Upcast_V2E )
    {
      Test_NS::Tetrahedron t;

      t.a.o().reset<Test_NS::Point3D>( 0, 0, 0 );
      t.b.o().reset<Test_NS::Point3D>( 1, 0, 0 );

      {
        Collision_NS::XVert x{ t.a };
        Assert::AreEqual( point( x ), point( x.toXEdge( t.a ) ) );
      }

      {
        Collision_NS::XVert x{ t.b };
        Assert::AreEqual( point( x ), point( x.toXEdge( t.a ) ) );
      }

      {
        Collision_NS::XVert x{ t.c };
        Assert::ExpectException<Collision_NS::BadUpcast>( [&]() { x.toXEdge( t.a ); } );
      }
    }


    TEST_METHOD( Upcast_V2F )
    {
      Test_NS::Tetrahedron t;

      t.a.o().reset<Test_NS::Point3D>( 0, 0, 0 );
      t.b.o().reset<Test_NS::Point3D>( 1, 0, 0 );
      t.c.o().reset<Test_NS::Point3D>( 0, 1, 0 );

      {
        Collision_NS::XVert x{ t.a };
        Assert::AreEqual( point( x ), fpoint( x.toXFace( t.a ) ) );
      }

      {
        Collision_NS::XVert x{ t.b };
        Assert::AreEqual( point( x ), fpoint( x.toXFace( t.a ) ) );
      }

      {
        Collision_NS::XVert x{ t.c };
        Assert::AreEqual( point( x ), fpoint( x.toXFace( t.a ) ) );
      }

      {
        Collision_NS::XVert x{ t.A };
        Assert::ExpectException<Collision_NS::BadUpcast>( [&]() { x.toXFace( t.a ); } );
      }
    }


    TEST_METHOD( Upcast_E2F )
    {
      Test_NS::Tetrahedron t;

      t.a.o().reset<Test_NS::Point3D>( 0, 0, 0 );
      t.b.o().reset<Test_NS::Point3D>( 1, 0, 0 );
      t.c.o().reset<Test_NS::Point3D>( 0, 1, 0 );

      {
        Collision_NS::XEdge x{ t.a, 1, 2 };
        Assert::AreEqual( point( x ), fpoint( x.toXFace( t.a ) ) );
      }

      {
        Collision_NS::XEdge x{ t.A, 1, 2 };
        Assert::ExpectException<Collision_NS::BadUpcast>( [&]() { x.toXFace( t.a ); } );
      }
    }
  };
}
