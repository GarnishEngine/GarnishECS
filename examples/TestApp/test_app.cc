#include "garnish_ecs.h"
#include <iostream>
#include <memory>
#include <string>

struct Person {
    std::string name;
};

void greet(std::shared_ptr<Person> p) {
    std::cout << "Hello, " << p->name << "!\n";
}

int main (void) {
    garnish::ECSManager ecs;

    Person bob = {
        .name = "Bob"
    };

    Person peter = {
        .name = "Peter"
    };

    ecs.RegisterComponent<Person>();
    auto e1 = ecs.CreateEntityWithComponents<Person>(bob);
    auto e2 = ecs.CreateEntityWithComponents<Person>(peter);

    auto entities = ecs.GetEntities<Person>();
    for (auto entity : entities) {
        std::shared_ptr<Person> p = ecs.GetComponent<Person>(entity);
        greet(p);
    }

    return 0;
}
