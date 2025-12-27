#pragma once
#include <any>
#include <string>
#include <unordered_map>
#include <vector>

#include "component_manager.h"
#include "ecs_common.h"
#include "entity_manager.h"
#include "resource_manager.h"
namespace garnish {
class ECSController final {
   public:
    ECSController()
        : componentManager(std::make_unique<ComponentManager>()),
          entityManager(std::make_unique<EntityManager>()),
          resourceManager(std::make_unique<ResourceManager>()) {}
    template <typename... Components>
    Entity create_entity_with_components(Components&&... components);
    Entity create_entity();

    template <typename... Components>
    std::vector<Entity> get_entities();
    std::vector<Entity> get_entities(Signature s);

    template <typename... Components, class F>
    void for_each(F&& f);

    void destroy_entity(Entity& e);

    template <typename... Components>
    void add_components(Entity e, Components&&... components);
    template <typename T>
    void add_component(Entity e, T&& component);

    template <typename T>
    ComponentType get_component_type();
    template <typename T>
    T& get_component(Entity e);
    template <typename T>
    bool has_component(Entity e);
    template <typename T>
    void register_component();
    template <typename T>
    void remove_component(Entity e);

    template <typename... Components>
    Signature get_signature();
    template <typename T>
    void set_system_signature(Signature signature);

    // void update_all();

    template <class T>
    void set(T&& value);
    template <class T>
    T& get();
    template <class T>
    T* try_get();
    template <class T>
    bool contains();
    template <class T>
    void remove();

    template <typename T>
    T& get_data(const std::string& name);
    void store_data(const std::string& name, std::any value);

   private:
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<ResourceManager> resourceManager;

    std::unordered_map<std::string, std::any> data;
};
}  // namespace garnish

#include "ecs_controller.tpp"
