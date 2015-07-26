#pragma once


#include <cinttypes>


namespace LongInt_NS
{
  template <typename H, typename L>
  struct LongIntRaw
  {
    L l;
    H h;

    unsigned add( const LongIntRaw& r, unsigned cf ) { return h.add( l.h, l.add( r.l, cf ) ); }
    unsigned sub( const LongIntRaw& r, unsigned cf ) { return h.sub( l.h, l.sub( r.l, cf ) ); }

    bool operator == ( const LongIntRaw& r ) const { return l == r.l && h == r.h; }
  };


  template <>
  struct LongIntRaw<uint32_t, uint32_t>
  {
    union
    {
      uint64_t u = 0;

      struct
      {
        uint32_t l;
        uint32_t h;
      };
    };

    LongIntRaw() = default;
    LongIntRaw( const LongIntRaw& ) = default;

    LongIntRaw( uint32_t l ) : h( 0u ), l( l ) {}
    LongIntRaw( uint32_t h, uint32_t l ) : h( h ), l( l ) {}
    LongIntRaw( uint64_t u ) : u( u ) {}

    unsigned add( const LongIntRaw& r ) { uint64_t v = u; u += r.u; return u < v; }
    unsigned add( const LongIntRaw& r, unsigned cf ) { return add( cf ) + add( r ); }

    unsigned sub( const LongIntRaw& r ) { uint64_t v = u; u -= r.u; return u > v; }
    unsigned sub( const LongIntRaw& r, unsigned cf ) { return sub( cf ) + sub( r ); }

    bool operator == ( const LongIntRaw& r ) const { return u == r.u; }
  };


  template <typename H, typename L>
  class LongInt
  {
    LongIntRaw<H, L> i;

  public:

    LongInt() = default;
    LongInt( const LongInt& ) = default;

    LongInt( uint32_t l ) : i( l ) {}

    LongInt& operator += ( const LongInt& r ) { i.add( r.i, 0 ); return *this; }
    LongInt& operator -= ( const LongInt& r ) { i.sub( r.i, 0 ); return *this; }

    friend bool operator == ( const LongInt& a, const LongInt& b ) { return a.i == b.i; }
    friend bool operator != ( const LongInt& a, const LongInt& b ) { return !( a == b ); }
  };
}