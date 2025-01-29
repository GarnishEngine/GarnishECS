
namespace garnish {
    template <typename T>
    void GarnishComponentArray<T>::AddData(GarnishEntity e, T component) {
        GARNISH_VALID_ENTITY();
        assert(EntityToIndex.find(e) == EntityToIndex.end() &&
                "Error: Entity already has this component");
        std::size_t NextIndex = CurrentIndex;
        ComponentArray[NextIndex] = component;
        EntityToIndex[e] = NextIndex;
        IndexToEntity[NextIndex] = e;
        CurrentIndex++;
    }

    template <typename T> 
    T &GarnishComponentArray<T>::GetData(GarnishEntity e) {
        GARNISH_VALID_ENTITY();
        assert(EntityToIndex.find(e) != EntityToIndex.end() &&
                "Error: Entity doesnt have this component");
        return ComponentArray[EntityToIndex[e]];
    }

    template <typename T>
    void GarnishComponentArray<T>::RemoveData(GarnishEntity e) {
        GARNISH_VALID_ENTITY();
        assert(EntityToIndex.find(e) != EntityToIndex.end() &&
                "Error: Entity doesnt have this component");

        // Move the last element to the removed element's index
        std::size_t IndexRemoved = EntityToIndex[e];
        std::size_t IndexOfLastElement = CurrentIndex - 1;
        // Ingore IndexOfLastElement as it will be overwriten when a new entity
        // gains this component
        ComponentArray[IndexRemoved] = ComponentArray[IndexOfLastElement];

        // update the maps
        GarnishEntity movedEntity = IndexToEntity[IndexOfLastElement];
        EntityToIndex[movedEntity] = IndexRemoved;
        IndexToEntity[IndexRemoved] = movedEntity;

        EntityToIndex.erase(e);
        IndexToEntity.erase(IndexOfLastElement);
        CurrentIndex--;
    }

    template <typename T>
    void GarnishComponentArray<T>::EntityDestroyed(GarnishEntity entity) {
        if (EntityToIndex.find(entity) != EntityToIndex.end()) {
            // Remove the entity's component if it existed
            RemoveData(entity);
        }
    };
    
    template<typename T> 
    void GarnishComponentManager::RegisterComponent() {
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
    GarnishComponentType GarnishComponentManager::GetComponentType() {
          const char* typeName = typeid(T).name();

          assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Component not registered before use.");

          // Return this component's type - used for creating signatures
          return ComponentTypes[typeName];
    }

    template<typename T>
    void GarnishComponentManager::AddComponent(GarnishEntity entity, T component) {
        // Add a component to the array for an entity
        GetComponentArray<T>()->AddData(entity, component);
    }
    template<typename T>
    void GarnishComponentManager::RemoveComponent(GarnishEntity entity) {
        // Remove a component from the array for an entity
        GetComponentArray<T>()->RemoveData(entity);
    }
    template<typename T>
    T& GarnishComponentManager::GetComponent(GarnishEntity entity) {
        // Get a reference to a component from the array for an entity
        return GetComponentArray<T>()->GetData(entity);
    }

    template<typename T>
    std::shared_ptr<GarnishComponentArray<T>> GarnishComponentManager::GetComponentArray() {
        const char* typeName = typeid(T).name();

        assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Error: Component not registered before use.");

        return std::static_pointer_cast<GarnishComponentArray<T>>(ComponentArrays[typeName]);
    }

} 
