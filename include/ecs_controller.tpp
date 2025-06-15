#pragma once
#include <utility>

#include "ecs_controller.h"
#include "ecs_common.h"

namespace garnish {
    template<typename... Components>
    Entity ECSController::create_entity_with_components(Components&&... components) {
        Entity e = create_entity();
        add_components<Components...>(e, std::forward<Components>(components)...);
        return e;
    }

    inline Entity ECSController::create_entity() {
        return entityManager->create_entity();
    }

    template<typename... Components>
    std::vector<Entity> ECSController::get_entities() {
        return get_entities(get_signature<Components...>());
    }

    inline std::vector<Entity> ECSController::get_entities(Signature s) {
        return entityManager->get_entities(s);
    }

    inline void ECSController::destroy_entity(Entity& e) {
        entityManager->destroy_entity(e);
    }
    
    template<typename T>
    ComponentType ECSController::get_component_type() {
        return componentManager->get_component_type<T>();
    }

    template<typename T>
    T& ECSController::get_component(Entity e) {
        return componentManager->get_component<T>(e);
    }

    template<typename T> 
    bool ECSController::has_component(Entity e) {
        Signature entSig = entityManager->get_entity_signature(e);
        Signature compSig = get_signature<T>();

        return (compSig & entSig) == compSig;
    }

    template<typename T>
    void ECSController::register_component() {
        componentManager->register_component<T>();
    }

    template<typename T>
    void ECSController::add_component(Entity e, T&& component) {
        componentManager->add_component<T>(e, std::forward<T>(component)); 
        entityManager->set_entity_signature(e, componentManager->get_component_type<T>());
    }
    
    template<typename... Components>
    void ECSController::add_components(Entity e, Components&&... components) {
        (add_component<Components>(e, std::forward<Components>(components)), ...);
    }

    template<typename... Components>
    Signature ECSController::get_signature() {
        Signature sig;
        (sig.set(componentManager->get_component_type<Components>()), ...);
        return sig;
    }

    template<typename T, typename ...Args>
    std::shared_ptr<T> ECSController::register_system(int priority, Args&&... args) {
        return systemManager->register_system<T>(priority, std::forward<Args>(args)...);
    }
    
    template<typename T>
    void ECSController::set_system_signature(Signature signature) {
        systemManager->set_signature<T>(signature);
    }

    inline void ECSController::update_all() {
        systemManager->update_all(*this);
    }

    template<typename T> 
    auto ECSController::get_data(const std::string &name) -> T& {
        return data[name];
    }

    inline void ECSController::store_data(const std::string &name, std::any value) {
        data[name] = std::move(value);
    }

}
