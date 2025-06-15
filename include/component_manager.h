#pragma once
#include "ecs_common.h"
#include "component_array.h"

namespace garnish {
    class ComponentManager {
    public:
        template<typename T>
        void register_component();
        
        template<typename T>
        void add_component(Entity entity, T&& component);

        template<typename T>
        void remove_component(Entity entity);

        template<typename T>
        ComponentType get_component_type();

        template<typename T>
        std::decay_t<T>& get_component(Entity entity);

        void entity_destroyed(Entity entity);

    private:
        template<typename T>
        std::shared_ptr<ComponentArray<std::decay_t<T>>> get_component_array();
        
        ComponentType nextComponentType;

        std::unordered_map<ComponentId, ComponentType> componentTypes;
        std::unordered_map<ComponentId, std::shared_ptr<IComponentArray>> componentArrays;
    };
}

#include "component_manager.tpp"
