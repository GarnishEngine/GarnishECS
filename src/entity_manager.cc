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

    if (auto it = entityToStringId.find(e); it != entityToStringId.end()) {
        stringIdToEntity.erase(it->second);
        entityToStringId.erase(it);
    }

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

void EntityManager::register_string_id(const std::string& id, Entity e) {
    garnish_valid_entity(e);
    assert(
        std::ranges::find(availableEntities, e) == availableEntities.end() &&
        "Error: Entity not registered"
    );

    if (auto existingIt = stringIdToEntity.find(id); 
        existingIt != stringIdToEntity.end() && existingIt->second != e) {
        entityToStringId.erase(existingIt->second);
    }

    if (auto entityIt = entityToStringId.find(e); entityIt != entityToStringId.end()) {
        stringIdToEntity.erase(entityIt->second);
    }

    stringIdToEntity[id] = e;
    entityToStringId[e] = id;
}

void EntityManager::unregister_string_id(const std::string& id) {
    if (auto it = stringIdToEntity.find(id); it != stringIdToEntity.end()) {
        entityToStringId.erase(it->second);
        stringIdToEntity.erase(it);
    }
}

Entity EntityManager::get_entity_by_string_id(const std::string& id) {
    if (auto it = stringIdToEntity.find(id); it != stringIdToEntity.end()) {
        return it->second;
    }
    return DEAD_ENTITY;
}

bool EntityManager::has_string_id(const std::string& id) {
    return stringIdToEntity.contains(id);
}

std::string EntityManager::get_string_id(Entity e) {
    garnish_valid_entity(e);
    if (auto it = entityToStringId.find(e); it != entityToStringId.end()) {
        return it->second;
    }
    return "";
}

bool EntityManager::entity_has_string_id(Entity e) {
    garnish_valid_entity(e);
    return entityToStringId.contains(e);
}
}  // namespace garnish
