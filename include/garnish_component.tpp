
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
} 
