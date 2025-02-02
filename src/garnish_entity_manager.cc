#include "garnish_entity_manager.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>

namespace garnish {
    EntityManager::EntityManager() {
        for (Entity i = 0; i < MAX_ENTITIES; i++) {
            AvailableEntities.push_back(i);
        }
    }

    Entity EntityManager::NewEntity() {
        assert(!AvailableEntities.empty() && "Error: Exceeded maximum entity count");

        Entity e = AvailableEntities.front();
        AvailableEntities.pop_front();
        return e;
    }

    void EntityManager::DestroyEntity(Entity e) {
        GARNISH_VALID_ENTITY();
        // Check if the entity id is valid and not available, this is why we use a deque instead of a queue
        assert(std::find(AvailableEntities.begin(), AvailableEntities.end(), e) == AvailableEntities.end() && "Error: Entity already available");
        
        Signatures[e] = 0;
        AvailableEntities.push_back(e);
    }

    Signature EntityManager::GetSignature(Entity e) {
        GARNISH_VALID_ENTITY();
        assert(std::find(AvailableEntities.begin(), AvailableEntities.end(), e) != AvailableEntities.end() && "Error: Entity Not registered");

        return Signatures[e];
    }

    void EntityManager::SetSignature(Entity e, ComponentType component) {
        GARNISH_VALID_ENTITY();

        Signatures[e].set(component);
    }

    std::vector<Entity> EntityManager::GetEntities(Signature s) {
        assert(s != 0 && "Error: cannot get empty entities, ensure your entity has a component or change your querry signature");

        std::vector<Entity> entities;
        for (Entity i = 0; i < AvailableEntities.front(); i++) {
            if ((Signatures[i] & s) == s) {
                entities.push_back(i);
            }
        }

        return entities;
    }
}
