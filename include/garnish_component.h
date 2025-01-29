#pragma once
#include <array>
#include <cassert>
#include <cstddef>
#include <memory>
#include <unordered_map>
#include "garnish_ecs_common.h"

namespace garnish {
    class IComponentArray {
        // The one instance of virtual inheritance in the entire implementation.
        // An interface is needed so that the ComponentManager (seen later)
        // can tell a generic ComponentArray that an entity has been destroyed
        // and that it needs to update its array mappings.
        public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
        public:
        void AddData(Entity e, T component);
        T &GetData(Entity e);
        void RemoveData(Entity e);
        void EntityDestroyed(Entity entity) override;

        private: 
        std::array<T, MAX_ENTITIES> ComponentArray;

        std::unordered_map<Entity, std::size_t> EntityToIndex;
        std::unordered_map<std::size_t, Entity> IndexToEntity;

        std::size_t CurrentIndex = 0;
    };

    class ComponentManager {
        public:
        template<typename T> void RegisterComponent();
        template<typename T> ComponentType GetComponentType();
        template<typename T> void AddComponent(Entity entity, T component);
        template<typename T> void RemoveComponent(Entity entity);
        template<typename T> T& GetComponent(Entity entity);
        void EntityDestroyed(Entity entity);

        private:
        std::unordered_map<const char*, ComponentType> ComponentTypes;
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> ComponentArrays;

        ComponentType NextComponentType{};

        // Convenience function to get the statically casted pointer to the ComponentArray of type T.
        template<typename T> std::shared_ptr<ComponentArray<T>> GetComponentArray();

    };
}

#include "garnish_component.tpp"
