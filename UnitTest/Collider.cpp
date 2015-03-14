#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Collision\Collider.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( Collider )
	{
    struct Point : public QEdge_NS::VertData
    {
      Point() = default;
      Point( const Math_NS::Vector3D& i_point ) : d_point( i_point ) {}
      Point( double x, double y, double z ) : d_point( x, y, z ) {}

      virtual Math_NS::Vector3D point() const { return d_point; }
      virtual void point( const Math_NS::Vector3D& i_point ) { d_point = i_point; }

    private:

      Math_NS::Vector3D d_point;
    };

	public:
		
    TEST_METHOD( Vert_Pos )
		{
      QEdge_NS::Shape s;

      auto e = s.makeLoop();

      e.o().reset<Point>( 0, 13, 42 );

      Collision_NS::Collider collider;

      bool r = collider( Collision_NS::Vert( e ), Collision_NS::Vert( e.sym() ) );

      Assert::IsTrue( r );
      Assert::AreEqual( 1u, collider.graph().all().size() );
		}

	};
}