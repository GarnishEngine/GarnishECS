#pragma once

#include <cassert>
#include <utility>

#include "resource_manager.h"

namespace garnish {
template <class T>
void ResourceManager::set(T&& value) {
    assert(!resources.contains(typeid(T)) && "ECS contains this resource");
    resources.emplace(typeid(T), std::forward<T>(value));
}
template <class T>
T& ResourceManager::get() {
    assert(
        resources.contains(typeid(T)) && "ECS does not contains this resource"
    );
    return std::any_cast<T&>(resources.at(typeid(T)));
}
template <class T>
T* ResourceManager::try_get() {
    return std::any_cast<T*>(resources.at(typeid(T)));
}

template <class T>
bool ResourceManager::contains() {
    return resources.contains(typeid(T));
}

template <class T>
void ResourceManager::remove() {
    assert(
        resources.contains(typeid(T)) && "ECS does not contains this resource"
    );
    resources.erase(typeid(T));
}
}  // namespace garnish