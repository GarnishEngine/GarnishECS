#pragma once
#include "component_array.h"
#include "ecs_common.h"

namespace garnish {
template <typename T>
template <typename U>
auto ComponentArray<T>::add_component(Entity e, U&& component) -> void
    requires std::is_same_v<std::decay_t<U>, std::decay_t<T>> {
    garnish_valid_entity(e);
    assert(
        !entityToIndex.contains(e) && "Error: Entity already has this component"
    );
    assert(currentIndex < MAX_ENTITIES);
    componentArray[currentIndex] = std::forward<U>(component);
    entityToIndex[e] = currentIndex;
    indexToEntity[currentIndex] = e;
    currentIndex++;
}

template <typename T>
void ComponentArray<T>::remove_component(Entity e) {
    garnish_valid_entity(e);
    assert(
        entityToIndex.contains(e) && "Error: Entity doesn't have this component"
    );
    std::size_t IndexRemoved = entityToIndex[e];
    std::size_t IndexOfLastElement = currentIndex - 1;
    componentArray[IndexRemoved] = componentArray[IndexOfLastElement];
    Entity movedEntity = indexToEntity[IndexOfLastElement];
    entityToIndex[movedEntity] = IndexRemoved;
    indexToEntity[IndexRemoved] = movedEntity;
    entityToIndex.erase(e);
    indexToEntity.erase(IndexOfLastElement);
    currentIndex--;
}

template <typename T>
T& ComponentArray<T>::get_component(Entity e) {
    garnish_valid_entity(e);
    assert(
        entityToIndex.contains(e) && "Error: Entity doesn't have this component"
    );
    return componentArray[entityToIndex[e]];
}

template <typename T>
void ComponentArray<T>::entity_destroyed(Entity entity) {
    if (entityToIndex.contains(entity)) {
        remove_component(entity);
    }
}
}  // namespace garnish