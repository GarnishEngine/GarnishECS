#pragma once
#include "ecs_common.h"


namespace garnish {
    template<typename T> class ComponentArray;
    class IComponentArray;
    using ComponentId = size_t;
    
    class ComponentInfo {
        static inline ComponentId g_NextComponentId{0};
    public:    
        template <typename T>
        static inline const ComponentId id = g_NextComponentId++;
    };

    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual auto entity_destroyed(Entity entity) -> void = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
    public:
        auto add_component(Entity e, T component) -> void;
        auto remove_component(Entity e) -> void;
        auto get_component(Entity e) -> T&;

        auto entity_destroyed(Entity entity) -> void override;
    private: 
        std::array<std::decay_t<T>, MAX_ENTITIES> ComponentArray;

        std::unordered_map<Entity, std::size_t> EntityToIndex;
        std::unordered_map<std::size_t, Entity> IndexToEntity;

        std::size_t CurrentIndex = 0;
    };
}

#include "component_array.tpp"
