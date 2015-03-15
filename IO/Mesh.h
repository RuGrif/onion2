#pragma once


#include "..\Collision\Graph.h"
#include "IO.h"


namespace IO_NS
{
  IO_API void writeMesh( const Collision_NS::Graph&, const std::wstring& );
}