#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\IO\STL.h"
#include "..\IO\Mesh.h"
#include "..\Collision\PrimCollider.h"
#include "..\Collision\AABBCollider.h"
#include "..\QEdge\Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS( AABBCollider )
	{
	public:
		
		TEST_METHOD( AABBCollision )
		{
      QEdge_NS::Shape a = IO_NS::readSTL( L"box.stl" );
      QEdge_NS::Shape b = IO_NS::readSTL( L"triple torus.stl" );

      auto fa = QEdge_NS::allFaces( a );
      auto fb = QEdge_NS::allFaces( b );

      Math_NS::Grid grid{ box( a ) + box( b ) };

      Collision_NS::AABBTree ta( fa, grid );
      Collision_NS::AABBTree tb( fb, grid );

      Collision_NS::Graph graph;
      Collision_NS::PrimCollider pc{ std::ref( graph ), grid };
      Collision_NS::AABBCollider c{ pc };

      c.collide( ta, tb );

      IO_NS::writeMesh( graph, L"box torus intersection.mesh" );
		}

	};
}