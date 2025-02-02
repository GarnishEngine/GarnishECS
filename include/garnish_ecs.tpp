#include "garnish_ecs.h"

namespace garnish {
    template<typename... Components>
    Entity ECSManager::CreateEntityWithComponents(Components... components) {
        Entity e = CreateEntity();
        AddComponents<Components...>(e, components...);
        return e;
    }

    template<typename T>
    void ECSManager::RegisterComponent() {
        componentManager->RegisterComponent<T>();
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
    ComponentType ECSManager::GetComponentType() {
        return componentManager->GetComponentType<T>();
    }

    template<typename T>
    T& ECSManager::GetComponent(Entity e) {
        return componentManager->GetComponent<T>(e);
    }
}
