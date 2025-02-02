#include "garnish_ecs.h"

namespace garnish {
    Entity ECSManager::CreateEntity() {
        return entityManager.CreateEntity();
    }

    void ECSManager::DestroyEntity(Entity& e) {
        entityManager.DestroyEntity(e);
    }

    std::vector<Entity> ECSManager::GetEntities(Signature s) {
        return entityManager.GetEntities(s);
    };

    void ECSManager::AddPlugin(void (*plugin)(ECSManager*)) {
        plugin(this);
    }
}
