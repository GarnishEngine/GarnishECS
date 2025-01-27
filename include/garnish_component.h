#pragma once
#include <array>
#include <cassert>
#include <cstddef>
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
  class GarnishComponentArray : IComponentArray {
    public:
      void AddEntity(GarnishEntity e, T component) {
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

      void RemoveEntity(GarnishEntity e, T component) {
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
          RemoveEntity(entity);
        }

      };

    private:
      std::array<T, MAX_ENTITIES> ComponentArray;

      std::unordered_map<GarnishEntity, std::size_t> EntityToIndex;
      std::unordered_map<std::size_t, GarnishEntity> IndexToEntity;

      std::size_t CurrentIndex = 0;
  };
}
