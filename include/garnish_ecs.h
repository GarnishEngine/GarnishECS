#pragma once
#include "garnish_ecs_common.h"
#include "garnish_component.h"
#include "garnish_entity.h"
#include "garnish_system.h"
#include <iostream>
#include <memory>
#include <vector>

namespace garnish {
    class GarnishECSManager {
        public:
        GarnishECSManager(); 

        template<typename... Components> void NewSystem(ECS_SYSTEM_TYPE type, void (*sys)(Components&...));

        void AddPlugin(void (*plugin)(GarnishECSManager*));

        template<typename... Components> std::vector<GarnishEntity> GetEntities();
        std::vector<GarnishEntity> GetEntities(GarnishSignature s);
        GarnishEntity NewEntity();

        template<typename... Components> GarnishSignature GetSignature(GarnishSignature s);
        template<typename T, typename... Components> GarnishSignature GetSignature(GarnishSignature s);
        template<typename T, typename... Components> GarnishSignature GetSignature();

        template<typename T> void NewComponent();
        template<typename T> GarnishComponentType GetComponentType();
        template<typename T> T& GetComponent(GarnishEntity e);

        template<typename T> void AddComponent(GarnishEntity e, T component);
        template<typename T> void AddComponents(GarnishEntity e, T component);
        template<typename T, typename... Components> void AddComponents(GarnishEntity e, T first, Components... rest);
        template<typename... Components> GarnishEntity NewEntityWithComponents(Components... components);

        private:
        std::unique_ptr<GarnishEntityManager> EntityManager;
        std::unique_ptr<GarnishComponentManager> ComponentManager;

    };
}

#include "garnish_ecs.tpp"