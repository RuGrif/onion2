#include <iostream>
#include "..\Collision\Collider.h"
#include "..\Collision\AABBCollider.h"
#include "..\IO\STL.h"
#include "..\IO\Mesh.h"
#include "..\QEdge\Utils.h"
#include <chrono>


void collision0() try
{
  auto t0 = std::chrono::high_resolution_clock::now();

  QEdge_NS::Shape a = IO_NS::readSTL( L"distort torus.stl" );
  QEdge_NS::Shape b = IO_NS::readSTL( L"triple torus.stl" );

  auto fa = QEdge_NS::allFaces( a );
  auto fb = QEdge_NS::allFaces( b );

  Collision_NS::Collider collider;

  for( auto a : fa ) for( auto b : fb ) collider( Collision_NS::Face( a ), Collision_NS::Face( b ) );

  IO_NS::writeMesh( collider.graph(), L"box - triple torus intersection.mesh" );

  auto t1 = std::chrono::high_resolution_clock::now();

  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>( t1 - t0 ).count() << " ms" << std::endl;
}
catch( const std::exception& e )
{
  std::cout << e.what() << std::endl;
}
catch( ... )
{
  std::cout << "(unknown error)" << std::endl;
}


void collision1() try
{
  auto t0 = std::chrono::high_resolution_clock::now();

  QEdge_NS::Shape a = IO_NS::readSTL( L"distort torus.stl" );
  QEdge_NS::Shape b = IO_NS::readSTL( L"triple torus.stl" );

  auto fa = QEdge_NS::allFaces( a );
  auto fb = QEdge_NS::allFaces( b );

  Math_NS::Grid g;

  Collision_NS::AABBTree ta( fa, g );
  Collision_NS::AABBTree tb( fb, g );

  Collision_NS::AABBCollider collider;

  collider.collideAll( ta, tb );

  IO_NS::writeMesh( collider.collider().graph(), L"box - triple torus intersection (AABB).mesh" );

  auto t1 = std::chrono::high_resolution_clock::now();

  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>( t1 - t0 ).count() << " ms" << std::endl;
}
catch( const std::exception& e )
{
  std::cout << e.what() << std::endl;
}
catch( ... )
{
  std::cout << "(unknown error)" << std::endl;
}


void main()
{
  collision1();
}