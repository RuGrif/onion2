#include "stdafx.h"
#include "CppUnitTest.h"
#include "Tetrahedron.h"
#include "../Collision/Primitive.h"
#include <set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS( ForEachNb )
	{
    struct Counter
    {
      size_t nV = 0;
      size_t nE = 0;
      size_t nF = 0;

      void operator()( Collision_NS::Vert ) { ++nV; }
      void operator()( Collision_NS::Edge ) { ++nE; }
      void operator()( Collision_NS::Face ) { ++nF; }
    };


	public:

		TEST_METHOD( VertNb )
		{
      Test_NS::Tetrahedron t;

      Collision_NS::Vert v{ t.a };

      Counter counter;

      v.forEachNb( [&counter]( auto e, auto v )
      {
        counter( v );
      } );

      Assert::AreEqual( 4u, counter.nV );
      Assert::AreEqual( 6u, counter.nE );
      Assert::AreEqual( 3u, counter.nF );
		}


    TEST_METHOD( EdgeNb )
    {
      Test_NS::Tetrahedron t;

      Collision_NS::Edge e{ t.a };

      Counter counter;

      e.forEachNb( [&counter]( auto e, auto v )
      {
        counter( v );
      } );

      Assert::AreEqual( 4u, counter.nV );
      Assert::AreEqual( 5u, counter.nE );
      Assert::AreEqual( 2u, counter.nF );
    }


    TEST_METHOD( FaceNb )
    {
      Test_NS::Tetrahedron t;

      Collision_NS::Face f{ t.a };

      Counter counter;

      f.forEachNb( [&counter]( auto e, auto v )
      {
        counter( v );
      } );

      Assert::AreEqual( 3u, counter.nV );
      Assert::AreEqual( 3u, counter.nE );
      Assert::AreEqual( 1u, counter.nF );
    }
	};
}