#include <iostream>
#include <string>
#include <limits>

#include "garnish_ecs.h"

struct A { 
    A() {
        // std::cout << "Constructor" << std::endl;
    }

    ~A() {
        // std::cout << "Destructor" << std::endl;
    }

    int val = 0;
};

int main (void) {
    garnish::ECSManager ecs;
    ecs.RegisterComponent<A>();

    auto e = ecs.CreateEntity();

    assert(!ecs.HasComponent<A>(e) && "Entity has component that has not been added to it");

    A a{};
    a.val = 0;
    ecs.AddComponent<A>(e, a);

    assert(ecs.HasComponent<A>(e) && "Entity does not have component just added to it");

    assert(ecs.GetComponent<A>(e).val == 0 && "Component does not have correct default value");

    ecs.GetComponent<A>(e).val = 3;

    assert(ecs.GetComponent<A>(e).val == 3 && "Component does not have correct value after it was assigned");
}