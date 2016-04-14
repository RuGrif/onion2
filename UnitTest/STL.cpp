#include "stdafx.h"
#include "CppUnitTest.h"
#include "../IO/STL.h"
#include "../QEdge/Utils.h"
#include "Point3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( STL )
  {
    Math_NS::Vector3D distort( const Math_NS::Vector3D& i_point )
    {
      Math_NS::Vector3D ex{ -0.7, 0.2, -0.4 };
      Math_NS::Vector3D ey{ -0.1, 0.3, 0.9 };
      Math_NS::Vector3D ez{ -0.1, 0.8, -0.1 };

      return{ i_point * ex, i_point * ey, i_point * ez };
    }

  public:

    TEST_METHOD( ReadBig )
    {
      QEdge_NS::Shape s;

      s = IO_NS::readSTL( L"triple torus.stl" );
      
      Assert::AreNotEqual( 0u, s.size() );

      for( QEdge_NS::Edge e : s )
      {
        Assert::IsTrue( e.o() );
        Assert::IsTrue( e.d() );
      }
    }
    

    TEST_METHOD( Read )
    {
      QEdge_NS::Shape s;
      
      s = IO_NS::readSTL( L"box.stl" );
      
      Assert::AreEqual( 18u, s.size() );

      for( QEdge_NS::Edge e : s )
      {
        Assert::IsTrue( e.o() );
        Assert::IsTrue( e.d() );
      }
    }


    TEST_METHOD( AllNodes )
    {
      QEdge_NS::Shape s = IO_NS::readSTL( L"box.stl" );

      Assert::AreEqual( 8u, QEdge_NS::allVerts( s ).size() );
      Assert::AreEqual( 12u, QEdge_NS::allFaces( s ).size() );
    }


    TEST_METHOD( Write )
    {
      QEdge_NS::Shape s = IO_NS::readSTL( L"box.stl" );

      IO_NS::writeSTL( s, L"unit test copy of box.stl" );

      QEdge_NS::Shape t = IO_NS::readSTL( L"unit test copy of box.stl" );

      Assert::AreEqual( s.size(), t.size() );
    }


    TEST_METHOD( WriteBig )
    {
      auto s = IO_NS::readSTL( L"triple torus.stl" );
      
      for( auto& v : QEdge_NS::allVerts( s ) )
      {
        v.o().reset<Test_NS::Point3D>( distort( v.o()->point() ) );
      }
      
      IO_NS::writeSTL( s, L"distort torus.stl" );
    }

  };
}