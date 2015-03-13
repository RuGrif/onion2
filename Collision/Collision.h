#pragma once


#ifdef COLLISION_EXPORTS
#define COLLISION_API __declspec(dllexport)
#else
#define COLLISION_API __declspec(dllimport)
#endif
