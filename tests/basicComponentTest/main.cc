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
};

int main (void) {
    garnish::ECSManager ecs;
    ecs.RegisterComponent<A>();

    auto e = ecs.CreateEntity();

    assert(!ecs.HasComponent<A>(e) && "Entity has component that has not been added to it");

    ecs.AddComponent<A>(e, A{ });

    assert(ecs.HasComponent<A>(e) && "Entity does not have component just added to it");
}