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
      template<typename... Components>
      void NewSystem(ECS_SYSTEM_TYPE type, void (*sys)(Components&...)) {
        // TODO: initialize the system and have it loop oever all entities
        // That have the specified components and run sys.
      }
      template<typename T>
      void NewComponent() {
        ComponentManager->RegisterComponent<T>();
      }

      template<typename T>
      GarnishComponentType GetComponentType() {
        return ComponentManager->GetComponentType<T>();
      }
      template<typename T>
      T& GetComponent(GarnishEntity e) {
        return ComponentManager->GetComponent<T>(e);
      }

      template<typename... Components>
      GarnishSignature GetSignature(GarnishSignature s) {
        return s;
      }

      template<typename T, typename... Components>
      GarnishSignature GetSignature(GarnishSignature s) {
        s.set(ComponentManager->GetComponentType<T>());
        return GetSignature<Components...>(s);
      }

      template<typename T, typename... Components>
      GarnishSignature GetSignature() {
        GarnishSignature s;
        s.set(ComponentManager->GetComponentType<T>());
        return GetSignature<Components...>(s);
      }
      
      template<typename... Components>
      std::vector<GarnishEntity> GetEntities() {
        return GetEntities(GetSignature<Components...>());
      }
      
      std::vector<GarnishEntity> GetEntities(GarnishSignature s);

      template<typename T>
      void AddComponent(GarnishEntity e, T component) {
        ComponentManager->AddComponent<T>(e,component); 
        EntityManager->SetSignature(e, ComponentManager->GetComponentType<T>());
      }
      template<typename T>
      void AddComponents(GarnishEntity e, T component) {
         AddComponent(e,component);
      }

      template<typename T, typename... Components>
      void AddComponents(GarnishEntity e, T first, Components... rest) {
         AddComponent(e,first);
         AddComponents(e,rest...);
      }
      template<typename... Components>
      GarnishEntity NewEntityWithComponents(Components... components) {
        GarnishEntity e = NewEntity();
        AddComponents<Components...>(e, components...);
        return e;
      }

      GarnishEntity NewEntity();
      void AddPlugin(void (*plugin)(GarnishECSManager*));

    private:
      std::unique_ptr<GarnishEntityManager> EntityManager;
      std::unique_ptr<GarnishComponentManager> ComponentManager;

  };
}
