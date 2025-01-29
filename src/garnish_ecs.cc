#include "garnish_ecs.h"

namespace garnish {
    ECSManager::ECSManager() {
        componentManager = std::make_unique<ComponentManager>();
        entityManager = std::make_unique<EntityManager>();
    }
    
    Entity ECSManager::NewEntity() {
        return entityManager->NewEntity();
    }

    std::vector<Entity> ECSManager::GetEntities(Signature s) {
        return entityManager->GetEntities(s);
    };

    void ECSManager::AddPlugin(void (*plugin)(ECSManager*)) {
        plugin(this);
    }
}
