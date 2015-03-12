#pragma once


#include "Vector3.h"
#include <utility>


template <> struct std::hash<Math_NS::Vector3F>;
template <> struct std::hash<std::pair<Math_NS::Vector3F, Math_NS::Vector3F>>;


#include "Hash.inl"