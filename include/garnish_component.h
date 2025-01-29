#pragma once
#include <array>
#include <cassert>
#include <cstddef>
#include <memory>
#include <unordered_map>
#include "garnish_ecs_common.h"

namespace garnish {
  // The one instance of virtual inheritance in the entire implementation.
  // An interface is needed so that the GarnishComponentManager (seen later)
  // can tell a generic ComponentArray that an entity has been destroyed
  // and that it needs to update its array mappings.
    
    class IComponentArray {
        public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(GarnishEntity entity) = 0;
    };

    template<typename T>
    class GarnishComponentArray : public IComponentArray {
        public:
        void AddData(GarnishEntity e, T component);
        T &GetData(GarnishEntity e);
        void RemoveData(GarnishEntity e);
        void EntityDestroyed(GarnishEntity entity) override;

        private: 
        std::array<T, MAX_ENTITIES> ComponentArray;

        std::unordered_map<GarnishEntity, std::size_t> EntityToIndex;
        std::unordered_map<std::size_t, GarnishEntity> IndexToEntity;

        std::size_t CurrentIndex = 0;
    };

    class GarnishComponentManager {
        public:
        template<typename T> void RegisterComponent();
        template<typename T> GarnishComponentType GetComponentType();
        template<typename T> void AddComponent(GarnishEntity entity, T component);
        template<typename T> void RemoveComponent(GarnishEntity entity);
        template<typename T> T& GetComponent(GarnishEntity entity);
        void EntityDestroyed(GarnishEntity entity);

        private:
        std::unordered_map<const char*, GarnishComponentType> ComponentTypes;
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> ComponentArrays;

        GarnishComponentType NextComponentType{};

        // Convenience function to get the statically casted pointer to the ComponentArray of type T.
        template<typename T>
        std::shared_ptr<GarnishComponentArray<T>> GetComponentArray();

    };
}

#include "garnish_component.tpp"
