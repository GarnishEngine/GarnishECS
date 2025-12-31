#pragma once

#include <bitset>
#include <cassert>
#include <cstddef>

namespace garnish {
using Entity = size_t;
using ComponentType = size_t;

constexpr Entity MAX_ENTITIES = 5000;
constexpr Entity DEAD_ENTITY = MAX_ENTITIES + 1;
constexpr ComponentType MAX_COMPONENTS = 2048;

using Signature = std::bitset<MAX_COMPONENTS>;

constexpr void garnish_valid_entity(Entity e) {
    assert(e < MAX_ENTITIES && e >= 0 && "Error: Invalid entity ID");
}

class ECSController;
}  // namespace garnish
