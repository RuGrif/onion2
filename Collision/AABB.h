#pragma once


#include "Primitive.h"
#include "../Math/Box3.h"
#include "../Math/Grid.h"
#include <vector>


//  Box storage structure
//    [current box id] [all left box ids] [all right box ids]
//  also we assume that left box contain s/2 primitives, right box - s-s/2; totally s
//  assume we need 1 boxes for 1 primitive; n primitives require F(n) = 2n-1 boxes
//    [current box   ] [left box        ] [right box        ]
//    [              ] [s/2 primitives  ] [s-s/2 primitives ]


namespace Collision_NS
{
  class AABBTree;


  class AABB
  {
  public:

    explicit AABB( const AABBTree& );

    using Box = Math_NS::Box3L;

    bool                isFace() const  { return d_begFace + 1 == d_endFace; }

    const Box&          box() const;
    Face                face() const;

    AABB                left() const;
    AABB                right() const;

  private:

    AABB( const AABBTree&, size_t, size_t, size_t );

    const AABBTree&     d_tree;
    size_t              d_begFace;
    size_t              d_endFace;
    size_t              d_boxId;
  };


  class AABBTree
  {
  public:

    using Box = Math_NS::Box3L;

    AABBTree( const std::vector<QEdge_NS::Edge>&, const Math_NS::Grid& );

    AABB        top()            const { return AABB( *this ); }
    const Box&  box ( size_t i ) const { return d_boxes.at( i ); }
    Face        face( size_t i ) const { return d_faces.at( i ); }
    size_t      size()           const { return d_faces.size(); }

  private:

    void split( const std::vector<QEdge_NS::Edge>&, const Math_NS::Grid& );
    void build( const Math_NS::Grid& );

  private:

    std::vector<Face>   d_faces;
    std::vector<Box>    d_boxes;
  };
}