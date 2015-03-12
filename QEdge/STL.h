#pragma once


#include "Shape.h"
#include <string>
#include "QEdge.h"


namespace QEdge_NS
{
  QEDGE_API Shape read( const std::wstring& );
  QEDGE_API void write( const std::wstring&, const Shape& );
}