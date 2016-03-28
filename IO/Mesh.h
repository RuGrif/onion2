#pragma once


#include "..\QEdge\Shape.h"
#include "IO.h"


namespace IO_NS
{
  IO_API void writeMesh( const QEdge_NS::Shape&, const std::wstring& );
}