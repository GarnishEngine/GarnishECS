#pragma once
#include "garnish_ecs_common.h"
#include "garnish_component.h"
#include "garnish_entity.h"
#include "garnish_system.h"
#include <iostream>
#include <memory>

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
      void AddComponent(GarnishEntity e, T component) {
        ComponentManager->AddComponent<T>(e,component); 
      }
      template<typename T>
      void AddComponents(GarnishEntity e, T component) {
        ComponentManager->AddComponent<T>(e,component); 
      }

      template<typename T, typename... Components>
      void AddComponents(GarnishEntity e, T first, Components... rest) {
         AddComponent(e,first);
         AddComponents(e,rest...);
      }

      void AddComponents(GarnishEntity e);

      GarnishEntity NewEntity();
      void AddPlugin(void (*plugin)(GarnishECSManager*));

      inline void hello() {
        std::cout << "Hello world!\n";
      };

    private:
      std::unique_ptr<GarnishEntityManager> EntityManager;
      std::unique_ptr<GarnishComponentManager> ComponentManager;
  };
}
