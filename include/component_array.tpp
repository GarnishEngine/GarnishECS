#pragma once
#include "component_array.h"

namespace garnish {
    template <typename T>
    void ComponentArray<T>::add_component(Entity e, T component) {
        GARNISH_VALID_ENTITY();
        assert(!EntityToIndex.contains(e) && "Error: Entity already has this component");
        std::size_t NextIndex = CurrentIndex;
        ComponentArray[NextIndex] = component;
        EntityToIndex[e] = NextIndex;
        IndexToEntity[NextIndex] = e;
        CurrentIndex++;
    }

    template <typename T>
    void ComponentArray<T>::remove_component(Entity e) {
        GARNISH_VALID_ENTITY();
        assert(EntityToIndex.contains(e) && "Error: Entity doesn't have this component");
        std::size_t IndexRemoved = EntityToIndex[e];
        std::size_t IndexOfLastElement = CurrentIndex - 1;
        ComponentArray[IndexRemoved] = ComponentArray[IndexOfLastElement];
        Entity movedEntity = IndexToEntity[IndexOfLastElement];
        EntityToIndex[movedEntity] = IndexRemoved;
        IndexToEntity[IndexRemoved] = movedEntity;
        EntityToIndex.erase(e);
        IndexToEntity.erase(IndexOfLastElement);
        CurrentIndex--;
    }

    template <typename T> 
    T& ComponentArray<T>::get_component(Entity e) {
        GARNISH_VALID_ENTITY();
        assert(EntityToIndex.contains(e) && "Error: Entity doesn't have this component");
        return ComponentArray[EntityToIndex[e]];
    }

    template <typename T>
    void ComponentArray<T>::entity_destroyed(Entity entity) {
        if (EntityToIndex.contains(entity)) {
            remove_component(entity);
        }
    }
}