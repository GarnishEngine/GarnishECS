#pragma once
#include <array>
#include <type_traits>

#include "ecs_common.h"

namespace garnish {
template <typename T>
class ComponentArray;
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

template <typename T>
class ComponentArray : public IComponentArray {
   public:
    ComponentArray();

    template <typename U>
    auto add_component(Entity entity, U&& component) -> void
        requires std::is_same_v<std::decay_t<U>, std::decay_t<T>>;
    auto remove_component(Entity entity) -> void;
    auto get_component(Entity entity) -> T&;

    auto entity_destroyed(Entity entity) -> void override;

   private:
    static constexpr std::size_t INVALID_INDEX = MAX_ENTITIES;

    std::array<std::decay_t<T>, MAX_ENTITIES> componentArray;

    std::array<std::size_t, MAX_ENTITIES> entityToIndex;
    std::array<Entity, MAX_ENTITIES> indexToEntity;

    std::size_t currentIndex = 0;
};
}  // namespace garnish

#include "component_array.tpp"
