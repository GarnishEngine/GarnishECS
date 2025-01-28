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
      void AddData(GarnishEntity e, T component) {
        GARNISH_VALID_ENTITY();
        assert(EntityToIndex.find(e) == EntityToIndex.end() && "Error: Entity already has this component");
        std::size_t NextIndex = CurrentIndex;
        ComponentArray[NextIndex] = component;
        EntityToIndex[e]=NextIndex;
        IndexToEntity[NextIndex]=e;
        CurrentIndex++; 
      }

      T& GetComponent(GarnishEntity e) {
        GARNISH_VALID_ENTITY();
        assert(EntityToIndex.find(e) != EntityToIndex.end() && "Error: Entity doesnt have this component");
        return &ComponentArray[EntityToIndex[e]];
      }

      void RemoveData(GarnishEntity e, T component) {
        GARNISH_VALID_ENTITY();
        assert(EntityToIndex.find(e) != EntityToIndex.end() && "Error: Entity doesnt have this component");

        // Move the last element to the removed element's index
        std::size_t IndexRemoved = EntityToIndex[e]; 
        std::size_t IndexOfLastElement = CurrentIndex-1; 
        // Ingore IndexOfLastElement as it will be overwriten when a new entity gains this component
        ComponentArray[IndexRemoved] = ComponentArray[IndexOfLastElement];
        
        // update the maps
        GarnishEntity movedEntity = IndexToEntity[IndexOfLastElement];
        EntityToIndex[movedEntity] = IndexRemoved;
        IndexToEntity[IndexRemoved] = movedEntity;

        EntityToIndex.erase(e);
        IndexToEntity.erase(IndexOfLastElement);
        CurrentIndex--; 
      }

      void EntityDestroyed(GarnishEntity entity) override {
        if (EntityToIndex.find(entity) != EntityToIndex.end()) {
          // Remove the entity's component if it existed
          // RemoveData(entity);
        }

      };

    private:
      std::array<T, MAX_ENTITIES> ComponentArray;

      std::unordered_map<GarnishEntity, std::size_t> EntityToIndex;
      std::unordered_map<std::size_t, GarnishEntity> IndexToEntity;

      std::size_t CurrentIndex = 0;
  };

  class GarnishComponentManager {
    public:
      template<typename T>
      void RegisterComponent(){
        const char* typeName = typeid(T).name();
        assert(ComponentTypes.find(typeName) == ComponentTypes.end() && "Error: Component is already registered");
        // Create new ComponentType
        // ComponentTypes.insert(typeName, NextComponentType);
        ComponentTypes[typeName] = NextComponentType;
        // Create new ComponentArray
        // ComponentArrays.insert(typeName, std::make_shared<GarnishComponentArray<T>>());
        std::shared_ptr<GarnishComponentArray<T>> ptr = std::make_shared<GarnishComponentArray<T>>();
        ComponentArrays[typeName] = ptr;
        NextComponentType++;
      }

      template<typename T>
      GarnishComponentType GetComponentType() {
          const char* typeName = typeid(T).name();

          assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Component not registered before use.");

          // Return this component's type - used for creating signatures
          return ComponentTypes[typeName];
        }

      template<typename T>
      void AddComponent(GarnishEntity entity, T component) {
        // Add a component to the array for an entity
        // GetComponentArray<T>()->InsertData(entity, component);
      }

      template<typename T>
      void RemoveComponent(GarnishEntity entity) {
        // Remove a component from the array for an entity
        // GetComponentArray<T>()->RemoveData(entity);
      }

      template<typename T>
      T& GetComponent(GarnishEntity entity) {
        // Get a reference to a component from the array for an entity
        return GetComponentArray<T>()->GetData(entity);
      }

      void EntityDestroyed(GarnishEntity entity);

    private:
      std::unordered_map<const char*, GarnishComponentType> ComponentTypes;
      std::unordered_map<const char*, std::shared_ptr<IComponentArray>> ComponentArrays;

      GarnishComponentType NextComponentType{};

      // Convenience function to get the statically casted pointer to the ComponentArray of type T.
      template<typename T>
      std::shared_ptr<GarnishComponentArray<T>> GetComponentArray() {
        const char* typeName = typeid(T).name();

        assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Error: Component not registered before use.");

        return std::static_pointer_cast<GarnishComponentArray<T>>(ComponentArrays[typeName]);
      }

  };
}
