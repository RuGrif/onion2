#include "STL.h"
#include "Constructor.h"
#include <fstream>


QEdge_NS::Shape IO_NS::readSTL( const std::wstring& i_fileName )
{
  QEdge_NS::Shape shape;
  IO_NS::Constructor constructor( shape );

  std::ifstream file( i_fileName, std::ifstream::binary );
  file.exceptions( file.badbit | file.failbit );

  file.seekg( 80 ); // header

  uint32_t nf = 0;
  file.read( reinterpret_cast<char*>( &nf ), 4 );

  for( uint32_t f = 0; f < nf; ++f )
  {
    float x[ 3 * 3 ];

    static_assert( sizeof( x ) == 3 * 3 * 4, "Invalid float[ 3 * 3 ] size" );

    file.seekg( 3 * 4, std::ifstream::cur ); //  normal
    file.read( reinterpret_cast<char*>( x ), 3 * 3 * 4 );
    file.seekg( 2, std::ifstream::cur );  //  attribute

    constructor.addTriangle(
      Math_NS::Vector3F( x[ 0 ], x[ 1 ], x[ 2 ] ), 
      Math_NS::Vector3F( x[ 3 ], x[ 4 ], x[ 5 ] ),
      Math_NS::Vector3F( x[ 6 ], x[ 7 ], x[ 8 ] ) );
  }

  return shape;
}


void IO_NS::writeSTL( const QEdge_NS::Shape& i_shape, const std::wstring& i_fileName )
{
  std::ofstream file( i_fileName, std::ofstream::binary );
  file.exceptions( file.badbit | file.failbit );

  char header[ 80 ] = "Garlyon STL file";
  file.write( header, 80 );
}
