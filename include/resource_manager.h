#pragma once
#include <any>
#include <cstddef>
#include <typeindex>
#include <unordered_map>

namespace garnish {
class ResourceManager final {
   public:
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

   private:
    std::unordered_map<std::type_index, std::any> resources;
};
}  // namespace garnish

#include "resource_manager.tpp"