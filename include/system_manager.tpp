#pragma once
#include "system_manager.h"

namespace garnish {
    template <typename T, typename ...Args>
    std::shared_ptr<T> SystemManager::register_system(int priority, Args&&... args) {
        const auto idx = SystemInfo::index_of<T>;

        assert(!systems.contains(idx));
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        systems_by_priority[priority].push_back(system);
        systems.emplace(idx, system);
        return system;
    }

    template<typename T>
    void SystemManager::set_signature(Signature signature) {
        const auto idx = SystemInfo::index_of<T>;
        assert(!systems.contains(idx));
        signatures[idx] = std::move(signature);
    }

    inline void SystemManager::entity_destroyed(Entity entity) {
        for (const auto &[_, system] : systems) {
            system->entities.erase(entity);
        }
    }

    inline void SystemManager::entity_signature_changed(Entity entity, Signature signature) {
        for (const auto &[type_name, system] : systems) {
            const auto &system_signature = signatures[type_name];
            // If system signature matches new signature (no change), keep/add entity
            // Otherwise, new signature doesn't match this system, ensure entity is remove if exists
            if ((signature & system_signature) == system_signature) {
                system->entities.insert(entity);
            } else {
                system->entities.erase(entity);
            }
        }
    }
    inline void SystemManager::update_all(ECSController &world) {
        for (auto &[_, system_list] : systems_by_priority) {
            for (auto &system : system_list) {
                system->update(world);
            }
        }
    }
}