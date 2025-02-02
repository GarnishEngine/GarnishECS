#pragma once
#include "garnish_ecs_common.h"
#include "garnish_component_manager.h"
#include "garnish_entity_manager.h"
#include <functional>
#include <memory>
#include <vector>

namespace garnish {
    class ECSManager {
    public:
        Entity CreateEntity();
        template<typename... Components> Entity CreateEntityWithComponents(Components... components);
        void DestroyEntity(Entity& e);

        template<typename T> void RegisterComponent();

        template<typename T> void AddComponent(Entity e, T component);
        template<typename T> void AddComponents(Entity e, T component);
        template<typename T, typename... Components> void AddComponents(Entity e, T first, Components... rest);

        template<typename... Components> Signature GetSignature(Signature s);
        template<typename T, typename... Components> Signature GetSignature(Signature s);
        template<typename T, typename... Components> Signature GetSignature();

        template<typename... Components> std::vector<Entity> GetEntities();
        std::vector<Entity> GetEntities(Signature s);

        template<typename T> ComponentType GetComponentType();
        template<typename T> T& GetComponent(Entity e);

        void AddPlugin(void (*plugin)(ECSManager*));

    private:
        EntityManager entityManager{ };
        ComponentManager componentManager{ };
    };
}

#include "garnish_ecs.tpp"
