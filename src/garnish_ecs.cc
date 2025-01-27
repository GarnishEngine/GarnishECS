#include "garnish_ecs.h"

namespace garnish {
  GarnishECSManager::GarnishECSManager() {
    ComponentManager = std::make_unique<GarnishComponentManager>();
		EntityManager = std::make_unique<GarnishEntityManager>();
  }
  void GarnishECSManager::AddPlugin(void (*plugin)(GarnishECSManager*)) {
    plugin(this);
  }
}
