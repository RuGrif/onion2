#pragma once


#include <type_traits>


namespace Tailor_NS
{
  template <bool Condition, typename Func, typename ... Args>
  std::enable_if_t<Condition> call_if( Func&& i_func, Args&& ...i_args )
  {
    i_func( std::forward<Args>( i_args )... );
  }
}