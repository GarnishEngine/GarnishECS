#include <iostream>
#include <string>
#include <limits>

#include "ecs_controller.h"

int main (void) {
    garnish::ECSController ecs;

    garnish::Entity ent = garnish::DEAD_ENTITY;
    ent = ecs.create_entity();

    assert(ent != garnish::DEAD_ENTITY && "First entity created is not dead");

    ecs.destroy_entity(ent);

    assert(ent == garnish::DEAD_ENTITY && "Killed entity is dead");
}