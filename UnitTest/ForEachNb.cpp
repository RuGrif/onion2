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
    using V = Collision_NS::Vert;
    using E = Collision_NS::Edge;
    using F = Collision_NS::Face;


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

      Counter vertCounter, edgeCounter;

      v.forEachNb( [&]( auto e, auto v )
      {
        edgeCounter( e );
        vertCounter( v );
      } );

      Assert::AreEqual( 1u, edgeCounter.nV );
      Assert::AreEqual( 6u, edgeCounter.nE );
      Assert::AreEqual( 6u, edgeCounter.nF );

      Assert::AreEqual( 4u, vertCounter.nV );
      Assert::AreEqual( 6u, vertCounter.nE );
      Assert::AreEqual( 3u, vertCounter.nF );
		}


    TEST_METHOD( EdgeNb )
    {
      Test_NS::Tetrahedron t;

      Collision_NS::Edge e{ t.a };

      Counter vertCounter, edgeCounter;

      e.forEachNb( [&]( auto e, auto v )
      {
        edgeCounter( e );
        vertCounter( v );
      } );

      Assert::AreEqual( 0u, edgeCounter.nV );
      Assert::AreEqual( 3u, edgeCounter.nE );
      Assert::AreEqual( 8u, edgeCounter.nF );

      Assert::AreEqual( 4u, vertCounter.nV );
      Assert::AreEqual( 5u, vertCounter.nE );
      Assert::AreEqual( 2u, vertCounter.nF );
    }


    TEST_METHOD( FaceNb )
    {
      Test_NS::Tetrahedron t;

      Collision_NS::Face f{ t.a };

      Counter vertCounter, edgeCounter;

      f.forEachNb( [&]( auto e, auto v )
      {
        edgeCounter( e );
        vertCounter( v );
      } );

      Assert::AreEqual( 0u, edgeCounter.nV );
      Assert::AreEqual( 0u, edgeCounter.nE );
      Assert::AreEqual( 7u, edgeCounter.nF );

      Assert::AreEqual( 3u, vertCounter.nV );
      Assert::AreEqual( 3u, vertCounter.nE );
      Assert::AreEqual( 1u, vertCounter.nF );
    }
	};
}