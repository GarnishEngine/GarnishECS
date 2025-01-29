#include "garnish_component.h"
#include <algorithm>
#include <cassert>
#include <cstddef>

namespace garnish {
    
    // Notify each component array that an entity has been destroyed
    // If it has a component for that entity, it will remove it
    void ComponentManager::EntityDestroyed(Entity entity) {
        for (auto const& pair : ComponentArrays)
        {
        auto const& component = pair.second;

        component->EntityDestroyed(entity);
        }
    }
}
