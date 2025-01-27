#include <iostream>
#include "garnish_ecs.h"

namespace garnish {
  void ECSManager::AddPlugin(void (*plugin)(ECSManager*)) {
    plugin(this);
  }
}
