#pragma once
#include <utility>

#include "ecs_common.h"
#include "ecs_controller.h"

namespace garnish {
template <typename... Components>
Entity ECSController::create_entity_with_components(
    Components&&... components
) {
    Entity e = create_entity();
    add_components<Components...>(e, std::forward<Components>(components)...);
    return e;
}

inline Entity ECSController::create_entity() {
    return entityManager->create_entity();
}

template <typename... Components>
std::vector<Entity> ECSController::get_entities() {
    return get_entities(get_signature<Components...>());
}

inline std::vector<Entity> ECSController::get_entities(Signature s) {
    return entityManager->get_entities(s);
}

template <typename... Components, class F>
void ECSController::for_each(F&& f) {
    auto sig = get_signature<Components...>();
    entityManager->for_each(sig, [this, &f](Entity e) mutable {
        std::forward<F>(f)(e, get_component<Components>(e)...);
    });
}

inline void ECSController::destroy_entity(Entity& e) {
    componentManager->entity_destroyed(e);
    entityManager->destroy_entity(e);
}

template <typename T>
ComponentType ECSController::get_component_type() {
    return componentManager->get_component_type<T>();
}

template <typename T>
T& ECSController::get_component(Entity e) {
    return componentManager->get_component<T>(e);
}

template <typename T>
bool ECSController::has_component(Entity e) {
    Signature entSig = entityManager->get_entity_signature(e);
    Signature compSig = get_signature<T>();

    return (compSig & entSig) == compSig;
}

template <typename T>
void ECSController::register_component() {
    componentManager->register_component<T>();
}

template <typename T>
void ECSController::add_component(Entity e, T&& component) {
    componentManager->add_component<T>(e, std::forward<T>(component));
    entityManager->set_entity_signature(
        e,
        componentManager->get_component_type<T>()
    );
}

template <typename... Components>
void ECSController::add_components(Entity e, Components&&... components) {
    (add_component<Components>(e, std::forward<Components>(components)), ...);
}

template <typename T>
void ECSController::remove_component(Entity e) {
    componentManager->remove_component<T>(e);
    entityManager->clear_entity_signature(
        e,
        componentManager->get_component_type<T>()
    );
}

template <typename... Components>
Signature ECSController::get_signature() {
    Signature sig;
    (sig.set(componentManager->get_component_type<Components>()), ...);
    return sig;
}

template <typename T>
auto ECSController::get_data(const std::string& name) -> T& {
    return std::any_cast<T&>(data.at(name));
}

inline void ECSController::store_data(const std::string& name, std::any value) {
    data[name] = std::move(value);
}

template <class T>
void ECSController::set(T&& value) {
    resourceManager->set<T>(std::forward<T>(value));
}
template <class T>
T& ECSController::get() {
    return resourceManager->get<T>();
}
template <class T>
T* ECSController::try_get() {
    return resourceManager->try_get<T>();
}

template <class T>
bool ECSController::contains() {
    return resourceManager->contains<T>();
}

template <class T>
void ECSController::remove() {
    resourceManager->remove<T>();
}
}  // namespace garnish
