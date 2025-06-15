#include "entity_manager.h"

namespace garnish {
    EntityManager::EntityManager() {
        for (Entity i = 0; i < MAX_ENTITIES; i++) {
            availableEntities.push_back(i);
        }
    }

    Entity EntityManager::create_entity() {
        assert(!availableEntities.empty() && "Error: Exceeded maximum entity count");

        Entity e = availableEntities.front();
        availableEntities.pop_front();
        return e;
    }

    void EntityManager::destroy_entity(Entity& e) {
        GARNISH_VALID_ENTITY();
        assert(std::find(availableEntities.begin(), availableEntities.end(), e) == availableEntities.end() && "Error: Entity already available");
        
        signatures[e] = 0;
        availableEntities.push_back(e);

        e = DEAD_ENTITY;
    }

    Signature EntityManager::get_entity_signature(Entity e) {
        GARNISH_VALID_ENTITY();
        assert(std::find(availableEntities.begin(), availableEntities.end(), e) == availableEntities.end() && "Error: Entity not registered");

        return signatures[e];
    }

    void EntityManager::set_entity_signature(Entity e, ComponentType component) {
        GARNISH_VALID_ENTITY();

        signatures[e].set(component);
    }

    std::vector<Entity> EntityManager::get_entities(Signature s) {
        assert(s.any() && "Error: cannot get empty entities");

        std::vector<Entity> entities;
        for (Entity i = 0; i < availableEntities.front(); i++) {
            if ((signatures[i] & s) == s) {
                entities.push_back(i);
            }
        }

        return entities;
    }
}
