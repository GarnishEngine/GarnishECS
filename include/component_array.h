#pragma once
#include "ecs_common.h"

namespace garnish {
    template<typename T> class ComponentArray;
    class IComponentArray;
    using ComponentId = size_t;
    
    class ComponentInfo {
        static inline ComponentId nextComponentId{0};
    public:    
        template <typename T>
        static inline const ComponentId id = nextComponentId++;
    };

    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual auto entity_destroyed(Entity entity) -> void = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
    public:
        auto add_component(Entity entity, T component) -> void;
        auto remove_component(Entity entity) -> void;
        auto get_component(Entity entity) -> T&;

        auto entity_destroyed(Entity entity) -> void override;
    private: 
        std::array<std::decay_t<T>, MAX_ENTITIES> componentArray;

        std::unordered_map<Entity, std::size_t> entityToIndex;
        std::unordered_map<std::size_t, Entity> indexToEntity;

        std::size_t currentIndex = 0;
    };
}

#include "component_array.tpp"
