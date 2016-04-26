#include <iostream>
#include "../Collision/PrimCollider.h"
#include "../Collision/AABBCollider.h"
#include "../Tailor/TopoGraph.h"
#include "../Tailor/Spider.h"
#include "../Tailor/Doppelganger.h"
#include "../Tailor/DeferSplice.h"
#include "../IO/STL.h"
#include "../IO/Mesh.h"
#include "../QEdge/Utils.h"
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

  if( argc != 1 + 4 )
  {
    std::cout << "run.exe <mesh1.stl> <mesh2.stl> <out1.mesh> <out2.mesh>" << std::endl;
    return;
  }
  else
  {
    std::wcout << L"run with " << argc << L" arguments" << std::endl;
    for( int i = 0; i < argc; ++i ) std::wcout << L"argv[" << i << L"] = " << argv[ i ] << std::endl;
  }

  Run_NS::TimeLog time;

  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Read STLs ... ";
  
  QEdge_NS::Shape a = IO_NS::readSTL( argv[ 1 ] );
  QEdge_NS::Shape b = IO_NS::readSTL( argv[ 2 ] );
  
  time.log();

  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Get faces ... ";
  
  auto fa = allFaces( a );
  auto fb = allFaces( b );
  
  time.log();

  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Get bounding box ... ";

  Math_NS::Grid grid{ box( a ) + box( b ) };

  time.log();

  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Build AABB trees ... ";

  Collision_NS::AABBTree ta( fa, grid );
  Collision_NS::AABBTree tb( fb, grid );

  time.log();

  /////////////////////////////////////////////////////////////////////////////

  Tailor_NS::TopoGraph graph;
  Collision_NS::PrimCollider primCollider{ std::ref( graph ), grid };
  Collision_NS::AABBCollider aabbCollider{ std::ref( primCollider ) };

  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Collide ... ";

  bool r = aabbCollider.collide( ta, tb );

  time.log();

  /////////////////////////////////////////////////////////////////////////////

  if( !r )
  {
    std::cout << "No intersection detected" << std::endl;
    return;
  }

  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Make twin edges ... ";

  Tailor_NS::Doppelganger doppelganger;
  doppelganger.shadow( graph );
  doppelganger.makeTwins();

  time.log();

  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Make spider web ... ";

  Tailor_NS::Spider spider;
  Tailor_NS::DeferSplice defer = spider.spin( graph, doppelganger );
  defer.splice();

  time.log();

  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Merge web ... ";

  a.merge( std::move( doppelganger.twinA() ) );
  b.merge( std::move( doppelganger.twinB() ) );
  a.merge( std::move( spider.webA() ) );
  b.merge( std::move( spider.webB() ) );

  doppelganger.substitute();

  a.cleanup();
  b.cleanup();

  time.log();

  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Save trimmed models ... ";

  IO_NS::writeMesh( a, argv[ 3 ] );
  IO_NS::writeMesh( b, argv[ 4 ] );

  time.log();


  /////////////////////////////////////////////////////////////////////////////

  auto t1 = std::chrono::high_resolution_clock::now();

  std::cout << "Overall executing time = " << std::chrono::duration_cast<std::chrono::milliseconds>( t1 - t0 ).count() << " ms" << std::endl;
}
catch( const Tailor_NS::DuplicatedXSpliceRay& e )
{
  std::cout << e.what() << " -> { " << e.id0 << ", " << e.id1 << " }" << std::endl;
}
catch( const std::exception& e )
{
  std::cout << e.what() << std::endl;
}
catch( ... )
{
  std::cout << "(unknown error)" << std::endl;
}