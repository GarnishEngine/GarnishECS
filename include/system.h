#pragma once
#include "ecs_common.h"
#include <set>

namespace garnish {
    class System {
    public: 
        System() = default;
        virtual ~System() = default;
        System(const System &) noexcept = delete;
        System(System &&) noexcept = delete;
        System &operator=(const System &) noexcept = delete;
        System &operator=(System &&) noexcept = delete;
        
        virtual void update(ECSController& world) = 0;

        std::set<Entity> entities;
    };
}