#pragma once
#include "component_array.h"

namespace garnish {
    template <typename T>
    void ComponentArray<T>::add_component(Entity e, T component) {
        GARNISH_VALID_ENTITY();
        assert(!entityToIndex.contains(e) && "Error: Entity already has this component");
        std::size_t NextIndex = currentIndex;
        componentArray[NextIndex] = component;
        entityToIndex[e] = NextIndex;
        indexToEntity[NextIndex] = e;
        currentIndex++;
    }

    template <typename T>
    void ComponentArray<T>::remove_component(Entity e) {
        GARNISH_VALID_ENTITY();
        assert(entityToIndex.contains(e) && "Error: Entity doesn't have this component");
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
        GARNISH_VALID_ENTITY();
        assert(entityToIndex.contains(e) && "Error: Entity doesn't have this component");
        return componentArray[entityToIndex[e]];
    }

    template <typename T>
    void ComponentArray<T>::entity_destroyed(Entity entity) {
        if (entityToIndex.contains(entity)) {
            remove_component(entity);
        }
    }
}