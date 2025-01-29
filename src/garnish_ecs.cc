#include "garnish_ecs.h"

namespace garnish {
    ECSManager::ECSManager() {
        componentManager = std::make_unique<ComponentManager>();
        entityManager = std::make_unique<EntityManager>();
        systemManager = std::make_unique<SystemManager>();
    }
    
    Entity ECSManager::NewEntity() {
        return entityManager->NewEntity();
    }

    std::vector<Entity> ECSManager::GetEntities(Signature s) {
        return entityManager->GetEntities(s);
    };

    void ECSManager::RunStartup() {
        systemManager->RunStartup(*this);
    }

    void ECSManager::RunUpdate() {
        systemManager->RunUpdate(*this);
    }

    void ECSManager::AddPlugin(void (*plugin)(ECSManager*)) {
        plugin(this);
    }
}
