#pragma once
#include "garnish_ecs_common.h"
#include "garnish_component.h"
#include "garnish_entity.h"
#include "garnish_system.h"
#include <iostream>
#include <memory>
#include <vector>

namespace garnish {
    class ECSManager {
        public:
        ECSManager(); 

        template<typename... Components> void NewSystem(ECS_SYSTEM_TYPE type, void (*sys)(Components&...));

        void AddPlugin(void (*plugin)(ECSManager*));

        template<typename... Components> std::vector<Entity> GetEntities();
        std::vector<Entity> GetEntities(Signature s);
        Entity NewEntity();

        template<typename... Components> Signature GetSignature(Signature s);
        template<typename T, typename... Components> Signature GetSignature(Signature s);
        template<typename T, typename... Components> Signature GetSignature();

        template<typename T> void NewComponent();
        template<typename T> ComponentType GetComponentType();
        template<typename T> T& GetComponent(Entity e);

        template<typename T> void AddComponent(Entity e, T component);
        template<typename T> void AddComponents(Entity e, T component);
        template<typename T, typename... Components> void AddComponents(Entity e, T first, Components... rest);
        template<typename... Components> Entity NewEntityWithComponents(Components... components);

        private:
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<ComponentManager> componentManager;

    };
}

#include "garnish_ecs.tpp"