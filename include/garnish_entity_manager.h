#pragma once
#include <array>
#include <deque>
#include <vector>
#include "garnish_ecs_common.h"

namespace garnish {
    class EntityManager {
    public:
        EntityManager();

        Entity NewEntity();
        void DeleteEntity(Entity e);

        Signature GetSignature(Entity e);
        std::vector<Entity> GetEntities(Signature s);

        void SetSignature(Entity e, ComponentType component);

    private:
        // Queue with available entity id's
        std::deque<Entity> AvailableEntities;

        std::array<Signature, MAX_ENTITIES> Signatures;
    };
}
