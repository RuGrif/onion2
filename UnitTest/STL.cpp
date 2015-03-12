#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\IO\STL.h"
#include "..\QEdge\Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( STL )
	{
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
      IO_NS::writeSTL( IO_NS::readSTL( L"triple torus.stl" ), L"unit test copy of triple torus.stl" );
    }

	};
}