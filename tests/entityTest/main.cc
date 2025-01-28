#include <iostream>
#include <string>
#include <limits>

#include "garnish_ecs.h"

int main (void) {
    garnish::GarnishECSManager ecs;

    garnish::GarnishEntity ent = std::numeric_limits<garnish::GarnishEntity>::max();
    ent = ecs.NewEntity();

    assert(ent == 0 && "First entity created does not have the first index");

    garnish::GarnishEntity ent2;
    for (size_t i = 1; i < garnish::MAX_ENTITIES; ++i) {
        ent2 = ecs.NewEntity();
    }

    assert(ent2 == garnish::MAX_ENTITIES - 1 && "Max entitys number is not being followed");
}