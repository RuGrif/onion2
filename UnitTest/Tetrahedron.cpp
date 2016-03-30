#include "stdafx.h"
#include "CppUnitTest.h"
#include "Tetrahedron.h"


Test_NS::Tetrahedron::Tetrahedron()
{
  //  make abc triangle
  a.sym().splice0( b );
  b.sym().splice0( c );
  c.sym().splice0( a );

  //  attach ABC ribs
  a.sym().splice0( C.sym() );
  b.sym().splice0( A.sym() );
  c.sym().splice0( B.sym() );

  //  close top vertex; from a top veiw order is CBA
  C.splice0( B );
  B.splice0( A );
}


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


TEST_CLASS( Tetrahedron )
{
  Test_NS::Tetrahedron t;

  void vert( QEdge_NS::Edge x, QEdge_NS::Edge y, QEdge_NS::Edge z )
  {
    Assert::AreEqual( y, x.oNext() );
    Assert::AreEqual( z, y.oNext() );
    Assert::AreEqual( x, z.oNext() );
  }

  void face( QEdge_NS::Edge x, QEdge_NS::Edge y, QEdge_NS::Edge z )
  {
    Assert::AreEqual( y, x.lNext() );
    Assert::AreEqual( z, y.lNext() );
    Assert::AreEqual( x, z.lNext() );
  }

public:

  TEST_METHOD( Faces )
  {
    face( t.a, t.b, t.c );
    face( t.a.sym(), t.B.sym(), t.C );
    face( t.b.sym(), t.C.sym(), t.A );
    face( t.c.sym(), t.A.sym(), t.B );
  }

  TEST_METHOD( Verts )
  {
    vert( t.C, t.B, t.A );
    vert( t.a, t.c.sym(), t.B.sym() );
    vert( t.b, t.a.sym(), t.C.sym() );
    vert( t.c, t.b.sym(), t.A.sym() );
  }
};