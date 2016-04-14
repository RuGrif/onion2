#include "stdafx.h"
#include "CppUnitTest.h"
#include "../IO/STL.h"
#include "../IO/Mesh.h"
#include "../Collision/PrimCollider.h"
#include "../Collision/AABBCollider.h"
#include "Intersection.h"
#include "../QEdge/Utils.h"
#include "Point3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( AABBCollider )
  {
    Math_NS::Vector3D distort( const Math_NS::Vector3D& i_point )
    {
      Math_NS::Vector3D ex{ -0.7, 0.2, -0.4 };
      Math_NS::Vector3D ey{ -0.1, 0.3, 0.9 };
      Math_NS::Vector3D ez{ -0.1, 0.8, -0.1 };

      return{ i_point * ex, i_point * ey, i_point * ez };
    }

  public:
    
    TEST_METHOD( AABBCollision )
    {
      QEdge_NS::Shape a = IO_NS::readSTL( L"box.stl" );
      QEdge_NS::Shape b = IO_NS::readSTL( L"box.stl" );

      for( auto v : allVerts( b ) ) v.o().reset<Test_NS::Point3D>( distort( v.o()->point() ) );

      auto fa = QEdge_NS::allFaces( a );
      auto fb = QEdge_NS::allFaces( b );

      Math_NS::Grid grid{ box( a ) + box( b ) };

      Test_NS::Intersection iAABB;

      {
        Collision_NS::AABBTree ta( fa, grid );
        Collision_NS::AABBTree tb( fb, grid );

        Collision_NS::PrimCollider pc{ std::ref( iAABB ), grid };
        Collision_NS::AABBCollider c{ pc };

        Assert::IsTrue( c.collide( ta, tb ) );
      }

      Test_NS::Intersection iDirect;

      {
        Collision_NS::PrimCollider pc{ std::ref( iDirect ), grid };
        for( Collision_NS::Face x : fa ) for( Collision_NS::Face y : fb )
        {
          pc( x, y );
        }
      }
      
      Assert::IsTrue( iDirect.d_xpoints == iAABB.d_xpoints, L"intersection" );
    }

  };
}