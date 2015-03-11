#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the QEDGE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// QEDGE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef QEDGE_EXPORTS
#define QEDGE_API __declspec(dllexport)
#else
#define QEDGE_API __declspec(dllimport)
#endif

//// This class is exported from the QEdge.dll
//class QEDGE_API CQEdge {
//public:
//	CQEdge(void);
//	// TODO: add your methods here.
//};
//
//extern QEDGE_API int nQEdge;
//
//QEDGE_API int fnQEdge(void);
