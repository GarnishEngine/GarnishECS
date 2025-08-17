#pragma once
#include <array>
#include <deque>
#include <vector>

#include "ecs_common.h"

namespace garnish {
class EntityManager final {
   public:
    EntityManager();

    Entity create_entity();
    void destroy_entity(Entity& e);
    std::vector<Entity> get_entities(Signature s);
    Signature get_entity_signature(Entity e);
    void set_entity_signature(Entity e, ComponentType component);

    template <class F>
    void for_each(Signature required, F&& f) {
        for (Entity i = 0; i < signatures.size(); ++i) {
            if ((signatures.at(i) & required) == required) {
                std::forward<F>(f)(i);
            }
        }
    }

   private:
    std::deque<Entity> availableEntities;
    std::array<Signature, MAX_ENTITIES> signatures;
};
}  // namespace garnish
