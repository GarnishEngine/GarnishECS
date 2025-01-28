#include "garnish_ecs.h"

namespace garnish {
  GarnishECSManager::GarnishECSManager() {
    ComponentManager = std::make_unique<GarnishComponentManager>();
		EntityManager = std::make_unique<GarnishEntityManager>();
  }
  
  GarnishEntity GarnishECSManager::NewEntity() {
    return EntityManager->NewEntity();
  }

  std::vector<GarnishEntity> GarnishECSManager::GetEntities(GarnishSignature s) {
    return EntityManager->GetEntities(s);
  };

  void GarnishECSManager::AddPlugin(void (*plugin)(GarnishECSManager*)) {
    plugin(this);
  }
}
