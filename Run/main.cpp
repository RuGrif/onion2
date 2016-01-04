#include <iostream>
#include "..\Collision\Collider.h"
#include "..\Collision\AABBCollider.h"
#include "..\IO\STL.h"
#include "..\IO\Mesh.h"
#include "..\QEdge\Utils.h"
#include "Log.h"


//void collision0() try
//{
//  auto t0 = std::chrono::high_resolution_clock::now();
//
//  QEdge_NS::Shape a = IO_NS::readSTL( L"box.stl" );
//  QEdge_NS::Shape b = IO_NS::readSTL( L"distort box.stl" );
//
//  auto fa = QEdge_NS::allFaces( a );
//  auto fb = QEdge_NS::allFaces( b );
//
//  Collision_NS::Collider collider;
//
//  for( auto a : fa ) for( auto b : fb ) collider( Collision_NS::Face( a ), Collision_NS::Face( b ) );
//
//  IO_NS::writeMesh( collider.graph(), L"run - direct intersection.mesh" );
//
//  auto t1 = std::chrono::high_resolution_clock::now();
//
//  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>( t1 - t0 ).count() << " ms" << std::endl;
//}
//catch( const std::exception& e )
//{
//  std::cout << e.what() << std::endl;
//}
//catch( ... )
//{
//  std::cout << "(unknown error)" << std::endl;
//}


bool validate( const QEdge_NS::Shape& s )
{
  for( const auto& v : QEdge_NS::allVerts( s ) )
  {
    if( !v.o() ) return false;
  }
  return true;
}


void wmain( int argc, wchar_t* argv[] )try
{
  auto t0 = std::chrono::high_resolution_clock::now();

  if( argc != 1 + 3 )
  {
    std::cout << "run.exe <mesh1.stl> <mesh2.stl> <intersection.mesh>" << std::endl;
    return;
  }
  else
  {
    std::wcout << L"run with " << argc << L" arguments" << std::endl;
    for( int i = 0; i < argc; ++i ) std::wcout << L"argv[" << i << L"] = " << argv[ i ] << std::endl;
  }

  Run_NS::TimeLog time;

  std::cout << "Read STLs ... ";
  
  QEdge_NS::Shape a = IO_NS::readSTL( argv[ 1 ] );
  QEdge_NS::Shape b = IO_NS::readSTL( argv[ 2 ] );
  
  time.log();

  std::cout << "Get faces ... ";
  
  auto fa = QEdge_NS::allFaces( a );
  auto fb = QEdge_NS::allFaces( b );
  
  time.log();

  Math_NS::Grid g;

  std::cout << "Build AABB trees ... ";

  Collision_NS::AABBTree ta( fa, g );
  Collision_NS::AABBTree tb( fb, g );

  time.log();

  Collision_NS::AABBCollider collider;

  std::cout << "Collide ... ";

  bool r = collider.collide( ta, tb );

  time.log();

  if( !r )
  {
    std::cout << "No intersection detected" << std::endl;
    return;
  }

  std::cout << "Save intersection graph ... ";

  IO_NS::writeMesh( collider.collider().graph(), argv[ 3 ] );

  time.log();

  auto t1 = std::chrono::high_resolution_clock::now();

  std::cout << "Overall executing time = " << std::chrono::duration_cast<std::chrono::milliseconds>( t1 - t0 ).count() << " ms" << std::endl;
}
catch( const std::exception& e )
{
  std::cout << e.what() << std::endl;
}
catch( ... )
{
  std::cout << "(unknown error)" << std::endl;
}