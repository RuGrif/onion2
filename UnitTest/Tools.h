#pragma once


#include "..\QEdge\Shape.h"


template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Loop<QEdge_NS::Vert>& e ) { return L"vert loop"; }
template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Loop<QEdge_NS::Face>& e ) { return L"face loop"; }

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Edge& e ) { return e ? QEdge_NS::Edge( e ).n()->tag() : L"null edge"; }

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Vert& v ) { return v ? v->tag() : L"null vert"; }
template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Face& f ) { return f ? f->tag() : L"null face"; }

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const Math_NS::Vector3I& v ) { return std::to_wstring( v.x ) + L", " + std::to_wstring( v.y ) + L", " + std::to_wstring( v.z ); }
template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const Math_NS::Vector3L& v ) { return std::to_wstring( v.x ) + L", " + std::to_wstring( v.y ) + L", " + std::to_wstring( v.z ); }

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const Math_NS::Vector3L::Type& t ) { return std::to_wstring( t ); }

void label( QEdge_NS::Edge, const std::wstring& = L"e" );