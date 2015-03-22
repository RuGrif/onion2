#include "AABB.h"
#include <algorithm>
#include <array>


Collision_NS::AABB::AABB( const AABBTree& i_tree, size_t i_beg, size_t i_end, size_t i_id )
  : d_tree(i_tree), d_begFace(i_beg), d_endFace(i_end), d_boxId( i_id )
{}


Collision_NS::AABB::AABB( const AABBTree& i_tree ) : AABB( i_tree, 0, i_tree.size(), 0 )
{}


const Collision_NS::AABB::Box& Collision_NS::AABB::box() const
{
  return d_tree.box( d_boxId );
}


Collision_NS::Face Collision_NS::AABB::face() const
{
  return d_tree.face( d_begFace );
}


Collision_NS::AABB Collision_NS::AABB::left() const
{
  size_t mid = ( d_begFace + d_endFace ) / 2;
  return{ d_tree, d_begFace, mid, d_boxId + 1 };
}


Collision_NS::AABB Collision_NS::AABB::right() const
{
  size_t mid = ( d_begFace + d_endFace ) / 2;
  return{ d_tree, mid, d_endFace, d_boxId + 2 * ( mid - d_begFace ) };
}


namespace
{
  class Split
  {
  public:

    using Vec = Math_NS::Vector3L;
    using Box = Math_NS::Box3<Vec::Type>;

    Split( const std::vector<QEdge_NS::Edge>& i_faces, const Math_NS::Grid& i_grid )
    {
      auto center = [i_grid]( Collision_NS::Face f ) { return i_grid( f.A().point() ) + i_grid( f.B().point() ) + i_grid( f.C().point() ); };
      size_t c = 0;

      std::transform( i_faces.begin(), i_faces.end(), std::back_inserter( d_centers ), center );
      std::generate_n( std::back_inserter( d_permutation ), i_faces.size(), [&c](){ return c++; } );

      split( 0, i_faces.size(), 0 );
    }

    const std::vector<size_t>& permutation() const { return d_permutation; }

  private:

    void split( size_t i_beg, size_t i_end, size_t i_axis )
    {
      if( i_end - i_beg <= 1 ) return;
        
      Vec::Type Vec::*A = d_axes[ i_axis ];
      size_t mid = ( i_beg + i_end ) / 2;

      auto o = d_permutation.begin();
      std::nth_element( o + i_beg, o + mid, o + i_end, [&]( size_t l, size_t r ) { return d_centers[ l ].*A < d_centers[ r ].*A; } );

      i_axis = ( i_axis + 1 ) % d_axes.size();

      split( i_beg, mid, i_axis );
      split( mid, i_end, i_axis );
    }

  private:

    std::vector<Vec>                  d_centers;
    std::vector<size_t>               d_permutation;
    std::array<Vec::Type Vec::*, 3>   d_axes;
  };


  //  box storage structure
  //    [current box id] [all left box ids] [all right box ids]
  //  bounding logic
  //    [current box   ] [left box        ] [right box        ]
  //    [              ] [s/2 primitives  ] [s-s/2 primitives ]
  class Hierarchy
  {
  public:
    
    Hierarchy( const std::vector<Collision_NS::Face>& i_faces, const Math_NS::Grid& i_grid )
      : d_faces( i_faces ), d_grid( i_grid ), d_boxes( 2 * i_faces.size() - 1 )
    {
      makeBox( 0, d_faces.size(), 0 );
    }

    std::vector<Math_NS::Box3L>& boxes() { return d_boxes; }

  private:

    const Math_NS::Box3L& makeBox( size_t i_beg, size_t i_end, size_t i_boxId )
    {
      auto& b = d_boxes.at( i_boxId );

      if( i_beg + 1 == i_end )
      {
        Collision_NS::Face f = d_faces.at( i_beg );
        b += d_grid( f.A().point() );
        b += d_grid( f.B().point() );
        b += d_grid( f.C().point() );
        return b;
      }
      else
      {
        size_t mid = ( i_beg + i_end ) / 2;
        return b = makeBox( i_beg, mid, i_boxId + 1 ) + makeBox( mid, i_end, i_boxId + 2 * ( mid - i_beg ) );
      }
    }
  
  private:

    std::vector<Collision_NS::Face>   d_faces;
    Math_NS::Grid                     d_grid;
    std::vector<Math_NS::Box3L>       d_boxes;
  };
}


Collision_NS::AABBTree::AABBTree( const std::vector<QEdge_NS::Edge>& i_faces, const Math_NS::Grid& i_grid )
{
  split( i_faces, i_grid );
  build( i_grid );
}


void Collision_NS::AABBTree::split( const std::vector<QEdge_NS::Edge>& i_faces, const Math_NS::Grid& i_grid )
{
  Split split( i_faces, i_grid );

  const std::vector<size_t>& p = split.permutation();

  for( size_t i = 0; i < p.size(); ++i )
  {
    d_faces.push_back( i_faces.at( p.at( i ) ) );
  }
}


void Collision_NS::AABBTree::build( const Math_NS::Grid& i_grid )
{
  Hierarchy hierarchy( d_faces, i_grid );
  std::swap( d_boxes, hierarchy.boxes() );
}