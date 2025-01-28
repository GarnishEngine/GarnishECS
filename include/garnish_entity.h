#pragma once
#include <array>
#include <deque>
#include <vector>
#include "garnish_ecs_common.h"

namespace garnish {

  class GarnishEntityManager {
    public:
      GarnishEntityManager();

      GarnishEntity NewEntity();
      void SetSignature(GarnishEntity e, GarnishComponentType component);
      GarnishSignature GetSignature(GarnishEntity e);
      std::vector<GarnishEntity> GetEntities(GarnishSignature s);
      void RemoveEntity(GarnishEntity e);

    private:
      // Queue with available entity id's
      std::deque<GarnishEntity> AvailableEntities;

      std::array<GarnishSignature,MAX_ENTITIES> Signatures;
  };
}
