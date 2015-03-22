#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\IO\STL.h"
#include "..\IO\Mesh.h"
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

      Math_NS::Grid g;

      Collision_NS::AABBTree ta( fa, g );
      Collision_NS::AABBTree tb( fb, g );

      Collision_NS::AABBCollider collider;

      collider.collide( ta, tb );

      IO_NS::writeMesh( collider.collider().graph(), L"box torus intersection.mesh" );
		}

	};
}