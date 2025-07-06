#pragma once
#include <map>
#include <unordered_map>
#include <vector>

#include "ecs_common.h"
#include "system.h"

namespace garnish {
class SystemManager final {
   public:
    template <typename T, typename... Args>
    std::shared_ptr<T> register_system(int priority, Args&&... args);

    template <typename T>
    void set_signature(Signature signature);

    void entity_destroyed(Entity entity);
    void entity_signature_changed(Entity entity, Signature signature);
    void update_all(ECSController& world);

   private:
    std::unordered_map<std::size_t, Signature> signatures;
    std::unordered_map<std::size_t, std::shared_ptr<System>> systems;
    std::map<int, std::vector<std::shared_ptr<System>>> systems_by_priority;
};

class SystemInfo {
    static inline std::size_t current_index = 0;

   public:
    template <typename T>
    static inline const std::size_t index_of = current_index++;
};
}  // namespace garnish

#include "system_manager.tpp"
