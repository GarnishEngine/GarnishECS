#pragma once
#include "garnish_system.h"
#include <iostream>
#include <utility>

namespace garnish {
  class ECSManager {
    public:
      template <typename... Components>
      void system(ECS_SYSTEM_TYPE type, void (*sys)(Components&...)) {
        // TODO: initialize the system and have it loop oever all entities
        // That have the specified components and run sys.
      }
      void AddPlugin(void (*plugin)(ECSManager*));
      inline void hello() {
        std::cout << "Hello world!\n";
      };
  };
}
