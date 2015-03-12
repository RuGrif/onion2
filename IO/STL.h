#pragma once


#include "..\QEdge\Shape.h"
#include <string.h>
#include "IO.h"


namespace IO_NS
{
  IO_API QEdge_NS::Shape readSTL( const std::wstring& );
  IO_API void writeSTL( const QEdge_NS::Shape&, const std::wstring& );
}