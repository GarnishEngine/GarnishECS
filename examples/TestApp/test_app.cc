#include "garnish_ecs.h"
#include <iostream>
#include <string>

struct Person {
  std::string name;
};

void greet(Person& p) {
  std::cout << "Hello, " << p.name << "!\n";
}

int main (void) {
  garnish::ECSManager ecs;

  Person bob = {
    .name = "Bob"
  };

  Person peter = {
    .name = "Peter"
  };

  ecs.NewComponent<Person>();
  auto e1 = ecs.NewEntityWithComponents<Person>(bob);
  auto e2 = ecs.NewEntityWithComponents<Person>(peter);

  auto entities = ecs.GetEntities<Person>();
  for (auto entity : entities) {
   Person& p = ecs.GetComponent<Person>(entity);
   greet(p);
  }

  return 0;
}
