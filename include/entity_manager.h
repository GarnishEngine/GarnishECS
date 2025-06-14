#pragma once
#include "ecs_common.h"
#include <deque>

namespace garnish {
    class EntityManager {
    public:
        EntityManager();

        Entity create_entity();
        void destroy_entity(Entity& e);
        std::vector<Entity> get_entities(Signature s);
        Signature get_entity_signature(Entity e);
        void set_entity_signature(Entity e, ComponentType component);
    private:
        // Queue with available entity id's
        std::deque<Entity> AvailableEntities;
        std::array<Signature, MAX_ENTITIES> Signatures;
    };
}
