#include "Data.h"


QEdge_NS::Tag::~Tag()
{

}


std::wstring QEdge_NS::Tag::tag() const
{
  return L"tag";
}


QEdge_NS::Vector3D QEdge_NS::VertData::point() const
{
  return{};
}


void QEdge_NS::VertData::point( const Vector3D& )
{

}


QEdge_NS::VertData::~VertData()
{

}
