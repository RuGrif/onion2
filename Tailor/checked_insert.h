#pragma once


#include <map>


namespace Tailor_NS
{
  struct DuplicatedMapEntry : std::exception { virtual const char* what() const override { return "Duplicated map entry"; } };


  template <typename Map, typename Key, typename Value>
  auto checked_insert( Map& map, Key&& key, Value&& value )
  {
    auto i = map.emplace( std::forward<Key>( key ), std::forward<Value>( value ) );
    
    if( !i.second )
    {
      throw DuplicatedMapEntry{};
    }

    return i.first;
  }
}