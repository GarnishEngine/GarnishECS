#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "garnish_ecs_common.h"

namespace garnish {
    class ECSManager;

    class ISystem {
    public:
        virtual void RunSystem(ECSManager& ecs) = 0;
    };

    template<typename... Components>
    class System : ISystem {
    public:
        System(std::function<void(Components...)> f);
        std::function<void(Components...)> SystemFunction;
        void RunSystem(ECSManager& ecs) override;
    };

    class SystemManager {
    public:
        template<typename... Components> void RegisterSystem(ECS_SYSTEM_TYPE type, std::function<void(Components...)> sys);
        void RunStartup(ECSManager& ecs);
        void RunUpdate(ECSManager& ecs);
    private:
        std::vector<std::shared_ptr<ISystem>> StartupSystems;
        std::vector<std::shared_ptr<ISystem>> UpdateSystems;
    };
}
#include "garnish_system.tpp"
