#pragma once
#include <array>
#include <deque>
#include <string>
#include <unordered_map>
#include <utility>
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
    void clear_entity_signature(Entity e, ComponentType component);

    void register_string_id(const std::string& id, Entity e);
    void unregister_string_id(const std::string& id);
    Entity get_entity_by_string_id(const std::string& id);
    bool has_string_id(const std::string& id);
    std::string get_string_id(Entity e);
    bool entity_has_string_id(Entity e);

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
    std::unordered_map<std::string, Entity> stringIdToEntity;
    std::unordered_map<Entity, std::string> entityToStringId;
};
}  // namespace garnish
