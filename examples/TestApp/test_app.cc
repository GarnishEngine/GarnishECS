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
  garnish::GarnishECSManager ecs;

  Person bob = {
    .name = "Bob"
  };

  ecs.AddPlugin([](garnish::GarnishECSManager* e){
    e->hello();
  });
  
  ecs.NewComponent<Person>();
  // auto entity = ecs.NewEntity();
  // ecs.AddComponents<Person>(entity, bob);

  // Implement the following code
  // ecs.NewSystem<Person>(ECS_SYSTEM_STARTUP, greet);
  // ecs.RunStartup();
  // while (ecs.RunUpdate());
  return 0;
}
