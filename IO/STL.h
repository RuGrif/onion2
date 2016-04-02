#pragma once


#include "..\QEdge\Shape.h"
#include <string.h>


namespace IO_NS
{
  QEdge_NS::Shape readSTL( const std::wstring& );
  void writeSTL( const QEdge_NS::Shape&, const std::wstring& );
}