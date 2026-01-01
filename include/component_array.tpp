#pragma once
#include "component_array.h"
#include "ecs_common.h"

namespace garnish {
template <typename T>
ComponentArray<T>::ComponentArray() {
    entityToIndex.fill(INVALID_INDEX);
}

template <typename T>
template <typename U>
auto ComponentArray<T>::add_component(Entity e, U&& component) -> void
    requires std::is_same_v<std::decay_t<U>, std::decay_t<T>> {
    garnish_valid_entity(e);
    assert(
        entityToIndex.at(e) == INVALID_INDEX && "Error: Entity already has this component"
    );
    assert(currentIndex < MAX_ENTITIES);
    componentArray.at(currentIndex) = std::forward<U>(component);
    entityToIndex.at(e) = currentIndex;
    indexToEntity.at(currentIndex) = e;
    currentIndex++;
}

template <typename T>
void ComponentArray<T>::remove_component(Entity e) {
    garnish_valid_entity(e);
    assert(
        entityToIndex.at(e) != INVALID_INDEX && "Error: Entity doesn't have this component"
    );
    std::size_t indexRemoved = entityToIndex.at(e);
    std::size_t indexOfLastElement = currentIndex - 1;
    componentArray.at(indexRemoved) = componentArray.at(indexOfLastElement);
    Entity movedEntity = indexToEntity.at(indexOfLastElement);
    entityToIndex.at(movedEntity) = indexRemoved;
    indexToEntity.at(indexRemoved) = movedEntity;
    entityToIndex.at(e) = INVALID_INDEX;
    currentIndex--;
}

template <typename T>
T& ComponentArray<T>::get_component(Entity e) {
    garnish_valid_entity(e);
    assert(
        entityToIndex.at(e) != INVALID_INDEX && "Error: Entity doesn't have this component"
    );
    return componentArray.at(entityToIndex.at(e));
}

template <typename T>
void ComponentArray<T>::entity_destroyed(Entity entity) {
    if (entityToIndex.at(entity) != INVALID_INDEX) {
        remove_component(entity);
    }
}
}  // namespace garnish