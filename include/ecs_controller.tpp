#pragma once
#include <iostream>
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

    if constexpr (SceneComponent<T>) {
        add_type<T>();
    }
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

void ECSController::register_string_id(const std::string& id, Entity e) {
    entityManager->register_string_id(id, e);
}

void ECSController::unregister_string_id(const std::string& id) {
    entityManager->unregister_string_id(id);
}

Entity ECSController::get_entity_by_string_id(const std::string& id) {
    return entityManager->get_entity_by_string_id(id);
}

bool ECSController::has_string_id(const std::string& id) {
    return entityManager->has_string_id(id);
}

std::string ECSController::get_string_id(Entity e) {
    return entityManager->get_string_id(e);
}

bool ECSController::entity_has_string_id(Entity e) {
    return entityManager->entity_has_string_id(e);
}

Entity ECSController::create_entity_with_string_id(const std::string& id) {
    Entity e = create_entity();
    register_string_id(id, e);
    return e;
}

template <typename... Components>
Entity ECSController::create_entity_with_string_id(
    const std::string& id,
    Components&&... components
) {
    Entity e = create_entity_with_components<Components...>(
        std::forward<Components>(components)...
    );
    register_string_id(id, e);
    return e;
}

template <SceneComponent C>
void ECSController::add_from_json(Entity e, const Json& j) {
    add_component<C>(e, C::from_json(j));
}
template <SceneComponent C>
void ECSController::add_type() {
    ComponentOps ops{
        .name = C::scene_name(),
        .add_from_json = [this](Entity e, const Json& j) {
            add_from_json<C>(e, j);
        },
    };
    componentRegistry_.emplace(ops.name, ops);
}

void ECSController::load_entity(Entity e, const Json& components) {
    for (auto it = components.begin(); it != components.end(); ++it) {
        std::string_view comp_name = it.key();
        const Json& comp_data = it.value();

        const auto& ops = componentRegistry_.find(comp_name);
        if (ops == componentRegistry_.end()) {
            throw std::runtime_error(
                std::format("Unknown component: {}", comp_name)
            );
        }

        ops->second.add_from_json(e, comp_data);
    }
}

}  // namespace garnish
