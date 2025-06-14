#include "entity_manager.h"

namespace garnish {
    EntityManager::EntityManager() {
        for (Entity i = 0; i < MAX_ENTITIES; i++) {
            AvailableEntities.push_back(i);
        }
    }

    Entity EntityManager::create_entity() {
        assert(!AvailableEntities.empty() && "Error: Exceeded maximum entity count");

        Entity e = AvailableEntities.front();
        AvailableEntities.pop_front();
        return e;
    }

    void EntityManager::destroy_entity(Entity& e) {
        GARNISH_VALID_ENTITY();
        assert(std::find(AvailableEntities.begin(), AvailableEntities.end(), e) == AvailableEntities.end() && "Error: Entity already available");
        
        Signatures[e] = 0;
        AvailableEntities.push_back(e);

        e = DEAD_ENTITY;
    }

    Signature EntityManager::get_entity_signature(Entity e) {
        GARNISH_VALID_ENTITY();
        assert(std::find(AvailableEntities.begin(), AvailableEntities.end(), e) == AvailableEntities.end() && "Error: Entity not registered");

        return Signatures[e];
    }

    void EntityManager::set_entity_signature(Entity e, ComponentType component) {
        GARNISH_VALID_ENTITY();

        Signatures[e].set(component);
    }

    std::vector<Entity> EntityManager::get_entities(Signature s) {
        assert(s.any() && "Error: cannot get empty entities");

        std::vector<Entity> entities;
        for (Entity i = 0; i < AvailableEntities.front(); i++) {
            if ((Signatures[i] & s) == s) {
                entities.push_back(i);
            }
        }

        return entities;
    }
}
