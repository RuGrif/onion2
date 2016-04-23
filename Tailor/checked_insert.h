#pragma once


namespace Tailor_NS
{
  struct DuplicatedMapEntry : std::exception { virtual const char* what() const override { return "Duplicated map entry"; } };
}