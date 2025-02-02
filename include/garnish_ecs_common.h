#pragma once
#include <cstdint>
#include <bitset>

namespace garnish {
    using Entity = std::uint32_t;
    using ComponentType = std::uint8_t;
    
    constexpr Entity MAX_ENTITIES = 5000;
    constexpr Entity DEAD_ENTITY = MAX_ENTITIES + 1;
    constexpr ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;

    #define GARNISH_VALID_ENTITY() assert(e < MAX_ENTITIES && e >= 0 && "Error: Invalid entity ID")
}

