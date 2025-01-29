#include "garnish_ecs.h"

namespace garnish {
    template<typename... Components>
    void ECSManager::NewSystem(ECS_SYSTEM_TYPE type, void (*sys)(Components&...)) {
        // TODO: initialize the system and have it loop oever all entities
        // That have the specified components and run sys.
    }

    template<typename T>
    void ECSManager::NewComponent() {
        componentManager->RegisterComponent<T>();
    }

    template<typename T>
    ComponentType ECSManager::GetComponentType() {
        return componentManager->GetComponentType<T>();
    }

    template<typename T>
    T& ECSManager::GetComponent(Entity e) {
        return componentManager->GetComponent<T>(e);
    }

    template<typename... Components>
    Signature ECSManager::GetSignature(Signature s) {
        return s;
    }

    template<typename T, typename... Components>
    Signature ECSManager::GetSignature(Signature s) {
        s.set(componentManager->GetComponentType<T>());
        return GetSignature<Components...>(s);
    }

    template<typename T, typename... Components>
    Signature ECSManager::GetSignature() {
        Signature s;
        s.set(componentManager->GetComponentType<T>());
        return GetSignature<Components...>(s);
    }
    
    template<typename... Components>
    std::vector<Entity> ECSManager::GetEntities() {
        return GetEntities(GetSignature<Components...>());
    }
    
    template<typename T>
    void ECSManager::AddComponent(Entity e, T component) {
        componentManager->AddComponent<T>(e,component); 
        entityManager->SetSignature(e, componentManager->GetComponentType<T>());
    }
    template<typename T>
    void ECSManager::AddComponents(Entity e, T component) {
        AddComponent(e,component);
    }

    template<typename T, typename... Components>
    void ECSManager::AddComponents(Entity e, T first, Components... rest) {
        AddComponent(e,first);
        AddComponents(e,rest...);
    }
    template<typename... Components>
    Entity ECSManager::NewEntityWithComponents(Components... components) {
        Entity e = NewEntity();
        AddComponents<Components...>(e, components...);
        return e;
    }
}