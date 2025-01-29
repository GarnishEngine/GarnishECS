#include "garnish_ecs.h"

namespace garnish {
    template<typename... Components>
    void GarnishECSManager::NewSystem(ECS_SYSTEM_TYPE type, void (*sys)(Components&...)) {
        // TODO: initialize the system and have it loop oever all entities
        // That have the specified components and run sys.
    }

    template<typename T>
    void GarnishECSManager::NewComponent() {
        ComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    GarnishComponentType GarnishECSManager::GetComponentType() {
        return ComponentManager->GetComponentType<T>();
    }

    template<typename T>
    T& GarnishECSManager::GetComponent(GarnishEntity e) {
        return ComponentManager->GetComponent<T>(e);
    }

    template<typename... Components>
    GarnishSignature GarnishECSManager::GetSignature(GarnishSignature s) {
        return s;
    }

    template<typename T, typename... Components>
    GarnishSignature GarnishECSManager::GetSignature(GarnishSignature s) {
        s.set(ComponentManager->GetComponentType<T>());
        return GetSignature<Components...>(s);
    }

    template<typename T, typename... Components>
    GarnishSignature GarnishECSManager::GetSignature() {
        GarnishSignature s;
        s.set(ComponentManager->GetComponentType<T>());
        return GetSignature<Components...>(s);
    }
    
    template<typename... Components>
    std::vector<GarnishEntity> GarnishECSManager::GetEntities() {
        return GetEntities(GetSignature<Components...>());
    }
    
    template<typename T>
    void GarnishECSManager::AddComponent(GarnishEntity e, T component) {
        ComponentManager->AddComponent<T>(e,component); 
        EntityManager->SetSignature(e, ComponentManager->GetComponentType<T>());
    }
    template<typename T>
    void GarnishECSManager::AddComponents(GarnishEntity e, T component) {
        AddComponent(e,component);
    }

    template<typename T, typename... Components>
    void GarnishECSManager::AddComponents(GarnishEntity e, T first, Components... rest) {
        AddComponent(e,first);
        AddComponents(e,rest...);
    }
    template<typename... Components>
    GarnishEntity GarnishECSManager::NewEntityWithComponents(Components... components) {
        GarnishEntity e = NewEntity();
        AddComponents<Components...>(e, components...);
        return e;
    }
}