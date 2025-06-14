#pragma once
#include "ecs_common.h"
#include "component_manager.h"
#include "entity_manager.h"
#include "system.h"
#include "system_manager.h"
#include <any>
#include <vector>
#include <deque>

namespace garnish {
    class ECSController {
    public:
        ECSController()
            : componentManager(std::make_unique<ComponentManager>()),
              entityManager(std::make_unique<EntityManager>()),
              systemManager(std::make_unique<SystemManager>()) {}
        template<typename... Components>
        Entity create_entity_with_components(Components&&... components);
        Entity create_entity();

        template<typename... Components>
        std::vector<Entity> get_entities();
        std::vector<Entity> get_entities(Signature s);

        void destroy_entity(Entity& e);

        template<typename... Components>
        void add_components(Entity e, Components&&... components);
        template<typename T>
        void add_component(Entity e, T&& component);

        template<typename T>
        ComponentType get_component_type();
        template<typename T>
        T& get_component(Entity e);
        template<typename T>
        bool has_component(Entity e);
        template<typename T>
        void register_component();

        template<typename T, typename ...Args>
        std::shared_ptr<T> register_system(int priority, Args&&... args);

        template<typename... Components>
        Signature get_signature();
        template<typename T>
        void set_system_signature(Signature signature);

        void update_all();

        template<typename T>
        T& get_data(const std::string &name);
        void store_data(const std::string &name, std::any value);

    private:
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<SystemManager> systemManager;

        std::unordered_map<std::string, std::any> data;
    };
}

#include "ecs_controller.tpp"
