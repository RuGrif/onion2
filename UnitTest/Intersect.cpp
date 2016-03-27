#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Collision\PrimCollider.h"
#include "..\IO\STL.h"
#include "..\IO\Mesh.h"
#include "..\QEdge\Utils.h"
#include "Point3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( Intersect )
	{
    Math_NS::Vector3D distort( const Math_NS::Vector3D& i_point )
    {
      Math_NS::Vector3D ex{ -0.7, 0.2, -0.4 };
      Math_NS::Vector3D ey{ -0.1, 0.3, 0.9 };
      Math_NS::Vector3D ez{ -0.1, 0.8, -0.1 };

      return{ i_point * ex, i_point * ey, i_point * ez };
    }

	public:
		
    TEST_METHOD( Box_Box )
		{
      QEdge_NS::Shape a = IO_NS::readSTL( L"box.stl" );
      QEdge_NS::Shape b = IO_NS::readSTL( L"box.stl" );

      for( auto& v : QEdge_NS::allVerts( b ) )
      {
        v.o().reset<Test_NS::Point3D>( distort( v.o()->point() ) );
      }

      IO_NS::writeSTL( b, L"distort box.stl" );

      auto fa = QEdge_NS::allFaces( a );
      auto fb = QEdge_NS::allFaces( b );

      Collision_NS::Graph graph;
      Collision_NS::PrimCollider collider{ std::ref( graph ), Math_NS::Grid{ box( a ) + box( b ) } };

      for( auto a : fa ) for( auto b : fb ) collider( Collision_NS::Face( a ), Collision_NS::Face( b ) );

      IO_NS::writeMesh( graph, L"box box intersection.mesh" );

      auto n = graph.all();

      Assert::AreNotEqual( 0u, n.size() );

      for( auto& i : n )
      {
        Assert::AreEqual( 2u, graph.neighborhood( i ).size() );
      }
		}
	};
}