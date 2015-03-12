#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\QEdge\STL.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( STL )
	{
	public:
		
		TEST_METHOD( Read )
		{
      QEdge_NS::Shape s;
      
      try
      {
        s = QEdge_NS::read( L"triple torus.stl" );
      }
      catch( ... )
      {
        Assert::IsTrue( false );
      }

      Assert::AreNotEqual( 0u, s.size() );
		}

	};
}