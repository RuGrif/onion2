#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Collision\AABB.h"
#include "..\IO\STL.h"
#include "..\QEdge\Utils.h"
#include <functional>
#include <numeric>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( AABB )
	{
    void allFaces( Collision_NS::AABB b, std::vector<Collision_NS::Face>& fs )
    {
      if( b.isFace() )
      {
        fs.push_back( b.face() );
      }
      else
      {
        allFaces( b.left(), fs );
        allFaces( b.right(), fs );
      }
    }


    Math_NS::Box3L faceCentersBox( const std::vector<Collision_NS::Face>& fs, const Math_NS::Grid& g )
    {
      return std::accumulate( fs.begin(), fs.end(), Math_NS::Box3L{}, [g]( Math_NS::Box3L b, Collision_NS::Face f )
      {
        return b += g( f.A().point() ) + g( f.B().point() ) + g( f.C().point() );
      } );
    }


    void checkBox( Collision_NS::AABB b, const Math_NS::Grid& i_grid )
    {
      Assert::IsFalse( b.isFace() );

      auto l = b.left();
      auto r = b.right();

      Assert::IsTrue( l.box().volume() <= b.box().volume(), L"left volume" );
      Assert::IsTrue( r.box().volume() <= b.box().volume(), L"right volume" );

      auto bb = l.box() + r.box();
      
      Assert::AreEqual( b.box().min, bb.min );
      Assert::AreEqual( b.box().max, bb.max );

      std::vector<Collision_NS::Face> lf, rf;
      allFaces( l, lf );
      allFaces( r, rf );

      if( ( lf.size() + rf.size() ) % 2 )
      {
        Assert::AreEqual( lf.size() + 1, rf.size(), L"50/50" );
      }
      else
      {
        Assert::AreEqual( lf.size(), rf.size(), L"50/50" );
      }

      auto lc = faceCentersBox( lf, i_grid );
      auto rc = faceCentersBox( rf, i_grid );

      Assert::IsTrue( lc.max.x <= rc.min.x || lc.max.y <= rc.min.y || lc.max.z <= rc.min.z, L"split" );
    }

    void checkFace( Collision_NS::AABB f, const Math_NS::Grid& i_grid )
    {
      Assert::IsTrue( f.isFace() );

      Collision_NS::AABB::Box b;
      b += i_grid( f.face().A().point() );
      b += i_grid( f.face().B().point() );
      b += i_grid( f.face().C().point() );

      Assert::AreEqual( f.box().min, b.min );
      Assert::AreEqual( f.box().max, b.max );

      auto l = f.left();
      auto r = f.right();
    }

    void check( Collision_NS::AABB b, const Math_NS::Grid& i_grid )
    {
      if( b.isFace() )
      {
        checkFace( b, i_grid );
      }
      else
      {
        checkBox( b, i_grid );
        check( b.left(), i_grid );
        check( b.right(), i_grid );
      }
    }

	public:
		
    TEST_METHOD( AABBTree )
		{
      QEdge_NS::Shape s = IO_NS::readSTL( L"box.stl" );

      Math_NS::Grid g{ box( s ) };

      Collision_NS::AABBTree tree( QEdge_NS::allFaces( s ), g );

      Collision_NS::AABB top = tree.top();

      check( top, g );
		}

    TEST_METHOD( TreeQuality )
    {
      QEdge_NS::Shape s = IO_NS::readSTL( L"triple torus.stl" );

      Math_NS::Grid g{ box( s ) };

      Collision_NS::AABBTree tree( QEdge_NS::allFaces( s ), g );

      Collision_NS::AABB top = tree.top();

      auto b = top.box().volume();
      auto l = top.left().box().volume();
      auto r = top.right().box().volume();

      Assert::IsTrue( 5 * l < 3 * b, L"left volume" );
      Assert::IsTrue( 5 * r < 3 * b, L"right volume" );

      //check( top, g );
    }

	};
}