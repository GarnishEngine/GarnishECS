#include <iostream>
#include <string>
#include <limits>

#include "ecs_controller.h"

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
    garnish::ECSController ecs;
    ecs.register_component<A>();

    auto e = ecs.create_entity();

    assert(!ecs.has_component<A>(e) && "Entity has component that has not been added to it");
    A a = A{};
    ecs.add_component(e, a);

    a.val = 0;

    assert(ecs.has_component<A>(e) && "Entity does not have component just added to it");

    assert(ecs.get_component<A>(e).val == 0 && "Component does not have correct default value");

    ecs.get_component<A>(e).val = 3;

    assert(ecs.get_component<A>(e).val == 3 && "Component does not have correct value after it was assigned");
    assert(ecs.has_component<A>(e) && "Entity does not have component just added to it");
}