#include <iostream>
#include <string>
#include <limits>

#include "garnish_ecs.h"

int main (void) {
    garnish::ECSManager ecs;

    garnish::Entity ent = garnish::DEAD_ENTITY;
    ent = ecs.CreateEntity();

    assert(ent != garnish::DEAD_ENTITY && "First entity created is not dead");

    ecs.DestroyEntity(ent);

    assert(ent == garnish::DEAD_ENTITY && "Killed entity is dead");
}