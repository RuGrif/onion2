#pragma once


#ifdef QEDGE_EXPORTS
#define QEDGE_API __declspec(dllexport)
#else
#define QEDGE_API __declspec(dllimport)
#endif
