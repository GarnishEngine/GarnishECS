#pragma once
#include <cassert>
#include <memory>
#include <type_traits>
#include "component_manager.h"

namespace garnish {
    template<typename T>
    void ComponentManager::register_component() {
        using U = std::decay_t<T>;
        ComponentId id = ComponentInfo::id<U>;

        assert(!componentTypes.contains(id));

        componentTypes[id]  = nextComponentType++;
        componentArrays[id] = std::make_shared<ComponentArray<U>>();
    }

    template<typename T>
    void ComponentManager::add_component(Entity entity, T&& component) {
        using U = std::decay_t<T>;
        get_component_array<U>()
            ->add_component(entity, std::forward<T>(component));
    }

    template<typename T>
    void ComponentManager::remove_component(Entity entity) {
        using U = std::decay_t<T>;
        get_component_array<U>()->remove_component(entity);
    }

    template<typename T>
    ComponentType ComponentManager::get_component_type() {
        using U = std::decay_t<T>;
        auto id = ComponentInfo::id<U>;
        assert(componentTypes.contains(id));
        return componentTypes.at(id);
    }

    template<typename T>
    std::decay_t<T>& ComponentManager::get_component(Entity entity) {
        using U = std::decay_t<T>;
        return get_component_array<U>()->get_component(entity);
    }

    template<typename T>
    std::shared_ptr<ComponentArray<std::decay_t<T>>>
    ComponentManager::get_component_array() {
        using U = std::decay_t<T>;
        auto id = ComponentInfo::id<U>;
        assert(componentTypes.contains(id));
        return std::static_pointer_cast<ComponentArray<U>>(componentArrays.at(id));
    }

    inline void ComponentManager::entity_destroyed(Entity entity) {
        for (auto const& [id, array] : componentArrays) {
            array->entity_destroyed(entity);
        }
    }
} 