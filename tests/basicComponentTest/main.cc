#include <iostream>
#include <string>
#include <limits>

#include "garnish_ecs.h"

struct A { };

int main (void) {
    garnish::ECSManager ecs;
    ecs.NewComponent<A>();

    auto ent = ecs.NewEntity();
    ecs.AddComponent<A>(ent, A{ });

    // assert(ecs.HasComponent<A>(ent) && "Entity dosent have component just added to it"); // TODO
}