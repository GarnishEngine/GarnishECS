#pragma once
#include "ecs_common.h"
#include <set>

namespace garnish {
    class System {
    public: 
        System() = default;
        virtual ~System() = default;
        System(const System &) noexcept = default;
        System(System &&) noexcept = default;
        System &operator=(const System &) noexcept = default;
        System &operator=(System &&) noexcept = default;
        
        virtual void update(ECSController& world) = 0;

        std::set<Entity> entities;
    };
}