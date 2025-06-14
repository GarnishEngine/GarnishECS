#include "ecs_common.h"
#include "ecs_controller.h"
#include <iostream>
#include <memory>
#include <string>

using namespace garnish;

struct Person {
    std::string name;
    int health;
};

struct Sword {
};

void greet(Person& p) {
    std::cout << p.name << " has " << p.health << " health!\n";
}

struct person_sys : System {
    void update(ECSController& world) override {
        for (Entity entity : world.get_entities<Person>()) {
            greet(world.get_component<Person>(entity));
            
        }
    }
};

struct sword_sys : System {
    void update(ECSController& world) override {
        for (Entity entity : world.get_entities<Person, Sword>()) {
            std::cout << world.get_component<Person>(entity).name << " has sword!\n";
        }
    }
};
int main (void) {
    ECSController ecs;

    Person bob = {
        .name = "Bob",
        .health = 3
    };

    Person peter = {
        .name = "Peter",
        .health = 5
    };

    ecs.register_component<Person>();
        ecs.register_component<Sword>();



    auto e1 = ecs.create_entity_with_components(bob, Sword{});
    auto e2 = ecs.create_entity_with_components(peter);
    ecs.register_system<person_sys>(0);
    ecs.register_system<sword_sys>(0);


    ecs.update_all();

    // auto entities = ecs.get_entities<Person>();
    // for (auto entity : entities) {
    //     Person& p = ecs.get_component<Person>(entity);
    //     greet(p);
    // }

    return 0;
}
