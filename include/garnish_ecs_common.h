#pragma once
#include <cstdint>
#include <bitset>

namespace garnish {
  using GarnishEntity = std::uint32_t;
  using GarnishComponentType = std::uint8_t;
  
  constexpr GarnishEntity MAX_ENTITIES = 5000;
  constexpr GarnishComponentType MAX_COMPONENTS = 32;

  using GarnishSignature = std::bitset<MAX_COMPONENTS>;

  #define GARNISH_VALID_ENTITY() assert(e < MAX_ENTITIES && e >= 0 && "Error: Invalid entity ID")
}

