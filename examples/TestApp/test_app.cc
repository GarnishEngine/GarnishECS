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

  ecs.AddPlugin([](garnish::ECSManager* e){
    e->hello();
  });

  // Implement the following code
  // ecs.Component<Person>();
  // auto entity = ecs.Entity();
  // ecs.AddComponents<Person>(entity, bob);
  // ecs.System<Person>(ECS_SYSTEM_STARTUP, greet);
  // ecs.RunStartup();
  // while (ecs.RunUpdate());
  return 0;
}
