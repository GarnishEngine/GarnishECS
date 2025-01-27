#pragma once
#include <array>
#include <deque>
#include "garnish_ecs_common.h"

namespace garnish {

  class GarnishEntityManager {
    public:
      GarnishEntityManager();

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
