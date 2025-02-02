namespace garnish {
    template <typename T>
    void ComponentArray<T>::AddData(Entity e, T component) {
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
    T &ComponentArray<T>::GetData(Entity e) {
        GARNISH_VALID_ENTITY();
        assert(EntityToIndex.find(e) != EntityToIndex.end() &&
                "Error: Entity doesnt have this component");
        return ComponentArray[EntityToIndex[e]];
    }

    template <typename T>
    void ComponentArray<T>::RemoveData(Entity e) {
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
        Entity movedEntity = IndexToEntity[IndexOfLastElement];
        EntityToIndex[movedEntity] = IndexRemoved;
        IndexToEntity[IndexRemoved] = movedEntity;

        EntityToIndex.erase(e);
        IndexToEntity.erase(IndexOfLastElement);
        CurrentIndex--;
    }

    template <typename T>
    void ComponentArray<T>::EntityDestroyed(Entity entity) {
        if (EntityToIndex.find(entity) != EntityToIndex.end()) {
            // Remove the entity's component if it existed
            RemoveData(entity);
        }
    }
    
    template<typename T> 
    void ComponentManager::RegisterComponent() {
        const char* typeName = typeid(T).name();
        assert(ComponentTypes.find(typeName) == ComponentTypes.end() && "Error: Component is already registered");
        // Create new ComponentType
        ComponentTypes[typeName] = NextComponentType;
        // Create new ComponentArray
        std::shared_ptr<ComponentArray<T>> ptr = std::make_shared<ComponentArray<T>>();
        ComponentArrays[typeName] = ptr;
        NextComponentType++;
    }

    template<typename T>
    ComponentType ComponentManager::GetComponentType() {
        const char* typeName = typeid(T).name();

        assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Component not registered before use.");

        // Return this component's type - used for creating signatures
        return ComponentTypes[typeName];
    }

    template<typename T>
    void ComponentManager::AddComponent(Entity entity, T component) {
        // Add a component to the array for an entity
        GetComponentArray<T>()->AddData(entity, component);
    }
    template<typename T>
    void ComponentManager::RemoveComponent(Entity entity) {
        // Remove a component from the array for an entity
        GetComponentArray<T>()->RemoveData(entity);
    }
    template<typename T>
    T& ComponentManager::GetComponent(Entity entity) {
        // Get a reference to a component from the array for an entity
        return GetComponentArray<T>()->GetData(entity);
    }

    template<typename T>
    std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray() {
        const char* typeName = typeid(T).name();

        assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Error: Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(ComponentArrays[typeName]);
    }
} 
