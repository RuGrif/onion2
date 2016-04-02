#pragma once


#include "../QEdge/Shape.h"


template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Loop<QEdge_NS::VertTraits>& e ) { return L"vert loop"; }
template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Loop<QEdge_NS::FaceTraits>& e ) { return L"face loop"; }

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Edge& e ) { return e ? ToString( e.id() ) : L"null edge"; }

template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Vert& v ) { return v ? v->tag() : L"null vert"; }
template <> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString( const QEdge_NS::Face& f ) { return f ? f->tag() : L"null face"; }


void label( QEdge_NS::Edge, const std::wstring& = L"e" );


namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template <typename T> std::wstring ToString( const boost::multiprecision::number<T>& i ) { return ToString( i.str() ); }
template <typename T> std::wstring ToString( const Math_NS::Vector3<T>& v ) { return ToString( v.x ) + L", " + ToString( v.y ) + L", " + ToString( v.z ); }

}}}