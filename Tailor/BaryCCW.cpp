#include "BaryCCW.h"
#include "Angle.h"


bool Tailor_NS::BaryCCW::operator()( const BaryF& l, const BaryF& r ) const
{
  return makeAngleC( l, o ) < makeAngleC( r, o );
}