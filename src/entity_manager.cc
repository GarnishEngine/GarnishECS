#include "entity_manager.h"

#include <algorithm>

#include "ecs_common.h"

namespace garnish {
EntityManager::EntityManager() {
    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        availableEntities.push_back(i);
    }
}

Entity EntityManager::create_entity() {
    assert(
        !availableEntities.empty() && "Error: Exceeded maximum entity count"
    );

    Entity e = availableEntities.front();
    availableEntities.pop_front();
    return e;
}

void EntityManager::destroy_entity(Entity& e) {
    garnish_valid_entity(e);
    assert(
        std::ranges::find(availableEntities, e) == availableEntities.end() &&
        "Error: Entity already available"
    );

    signatures.at(e) = 0;
    availableEntities.push_back(e);

    e = DEAD_ENTITY;
}

Signature EntityManager::get_entity_signature(Entity e) {
    garnish_valid_entity(e);
    assert(
        std::ranges::find(availableEntities, e) == availableEntities.end() &&
        "Error: Entity not registered"
    );

    return signatures.at(e);
}

void EntityManager::set_entity_signature(Entity e, ComponentType component) {
    garnish_valid_entity(e);

    signatures.at(e).set(component);
}

void EntityManager::clear_entity_signature(Entity e, ComponentType component) {
    garnish_valid_entity(e);
    signatures.at(e).reset(component);
}

std::vector<Entity> EntityManager::get_entities(Signature s) {
    assert(s.any() && "Error: cannot get empty entities");

    std::vector<Entity> entities;
    for (Entity i = 0; i < signatures.size(); i++) {
        if ((signatures.at(i) & s) == s) {
            entities.push_back(i);
        }
    }

    return entities;
}
}  // namespace garnish
