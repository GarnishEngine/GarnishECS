#include "garnish_ecs_common.h"

namespace garnish {
    template<typename... Components> 
    System<Components...>::System(std::function<void(Components...)> f) {
      SystemFunction = f;
    }

    template<typename... Components> 
    void System<Components...>::RunSystem(ECSManager& ecs) {
      auto entities = ecs.GetEntities<Components...>();
      for (auto entity : entities) {
        SystemFunction(ecs.GetComponents<Components>(entity),...);
      }
    }

    template<typename... Components> 
    void SystemManager::RegisterSystem(ECS_SYSTEM_TYPE type, std::function<void(Components...)> sys) {
      if (type == ECS_SYSTEM_STARTUP) {
        std::shared_ptr<System<Components...>> s = std::make_shared<System<Components...>>();
        StartupSystems.push_back(s);
      }
      if (type == ECS_SYSTEM_UPDATE) {
        System<Components...> s(sys);
        UpdateSystems.push_back(s);
      }
    }
    void SystemManager::RunStartup(ECSManager& ecs) {
      for (auto system : StartupSystems) {
        system->RunSystem(ecs);
      }
    }
    void SystemManager::RunUpdate(ECSManager& ecs) {
      for (auto system : UpdateSystems) {
        system->RunSystem(ecs);
      }
    }
}

