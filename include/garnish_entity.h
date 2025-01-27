#pragma once
#include <array>
#include <bitset>
#include <cstdint>
#include <deque>
#include "garnish_component.h"

namespace garnish {
  using GarnishEntity = std::uint32_t;

  constexpr GarnishEntity MAX_ENTITIES = 5000;

  using GarnishSignature = std::bitset<MAX_COMPONENTS>;

  class EntityManager {
    public:
      EntityManager();

      GarnishEntity NewEntity();
      void SetSignature(GarnishEntity e, GarnishSignature s);
      GarnishSignature GetSignature(GarnishEntity e);
      void RemoveEntity(GarnishEntity e);

    private:
      // Queue with available entity id's
      std::deque<GarnishEntity> AvailableEntities;

      std::array<GarnishSignature,MAX_ENTITIES> Signatures;
  };
}
